#pragma once
#include <windows.networking.sockets.h>
#include "Packets.h"
#include "conio.h"
#include <vector>
#include <map>
#include <string>
//Client
enum class ClientState { Welcome, Lobby, Chatroom };
ClientState currentState;
//current user and chatroom
AccountData currentUser;
ChatroomData currentChatroom;
//list of chatrooms current user's in
vector<ChatroomData> chatroomList;
//
map<long, vector<AccountData>> chatroomMemberMap;
map<long, vector<MessageData>> chatroomMessageMap;
int cursor;
int errorFlag=0;
void DisplayError()
{
	switch (errorFlag)
	{
	case 0:
		break;
	case 1:
		cout << "Error: Username taken" << endl;
		break;
	case 2:
		cout << "Error: Wrong username or password" << endl;
		break;
	case 3:
		cout << "Error: Did not find matching chatroom" << endl;
		break;
	}
}
void copyChatroomList(char* src, int num)
{
	ChatroomData buffer;
	for (int i = 0; i < num; i++)
	{
		memcpy(&buffer, src + i * sizeof(ChatroomData), sizeof(ChatroomData));
		chatroomList.push_back(buffer);
		chatroomMemberMap.insert(pair<int,vector<AccountData>>(buffer.chatroomID,vector<AccountData>()));
		chatroomMessageMap.insert(pair<int, vector<MessageData>>(buffer.chatroomID, vector<MessageData>()));
	}
}
//receive response from server, return true if server responses success, return false if otherwise
void recvResponse(SOCKET socket)
{
	
		char RxBuffer[1024] = {};
	while (1)
	{
		recv(socket, RxBuffer, sizeof(RxBuffer), 0);
		char RxPacketType[typeNameSize] = {};
		memcpy(RxPacketType, RxBuffer, typeNameSize);
		//received server response
		if (memcmp(RxPacketType, typeResponse, typeNameSize) == 0)
		{
			
			char Buffer[sizeof(HeaderPacket)] = {};
			//memcpy(Buffer, RxBuffer + typeNameSize, sizeof(HeaderPacket));
			memcpy(Buffer, RxBuffer, sizeof(HeaderPacket));
			HeaderPacket rxPkt(Buffer);
			//rxPkt.Print();
			//received register/login success message
			if (strncmp(rxPkt.getResponse(), respLoginSuccess, responseSize) == 0 || strncmp(rxPkt.getResponse(), respRegisterSuccess, responseSize) == 0)
			{
				errorFlag = 0;
				AccountPacket accountBuffer(RxBuffer + sizeof(HeaderPacket));
				currentUser = accountBuffer.GetAccountData();
				cursor = 0;
				currentState = ClientState::Lobby;
			}
			//received list of chatroom data
			else if (strncmp(rxPkt.getResponse(), respChatroomList, responseSize) == 0)
			{
				errorFlag = 0;
				copyChatroomList(RxBuffer + sizeof(HeaderPacket), rxPkt.getPacketNum());
			}
			//received list of chatroom member
			else if (strncmp(rxPkt.getResponse(), respMemberList, responseSize) == 0)
			{
				errorFlag = 0;
				long IDbuffer;
				
				memcpy(&IDbuffer, RxBuffer + sizeof(HeaderPacket), sizeof(long));
				for (int i = 0; i < rxPkt.getPacketNum(); i++)
				{
					AccountData temp;
					memcpy(&temp, RxBuffer + sizeof(HeaderPacket) + sizeof(long) + sizeof(AccountData) * i, sizeof(AccountData));
					chatroomMemberMap[IDbuffer].push_back(temp);
				}
			}
			//received list of chatroom messages
			else if (strncmp(rxPkt.getResponse(), respMessageList, responseSize) == 0)
			{
				errorFlag = 0;
				for (int i = 0; i < rxPkt.getPacketNum(); i++)
				{
					MessageData temp;
					memcpy(&temp, RxBuffer + sizeof(HeaderPacket) + sizeof(MessageData) * i, sizeof(MessageData));
					chatroomMessageMap[temp.chatroomID].push_back(temp);
				}
			}
			else if (strncmp(rxPkt.getResponse(), respRegisterFail, responseSize) == 0)
				errorFlag = 1;
			else if (strncmp(rxPkt.getResponse(), respLoginFail, responseSize) == 0)
				errorFlag = 2;
			else if (strncmp(rxPkt.getResponse(), respJoinRoomFail, responseSize) == 0)
				errorFlag = 3;
		}
	}
	
	//return -1;
}

//Last parameter defines whether it's register or login action. 0 for register and 1 for login. Return true if action succeeded
void RegisterLogin(SOCKET socket, char* username,char* password, int i)
{
	char TxBuffer[1024] = {};
	char RxBuffer[1024] = {};
	Packet* pkt;
	if (i == 0)
		pkt = new AccountPacket(actionRegister, username, password);
	else if(i==1)
		pkt = new AccountPacket(actionLogin, username, password);
	else if (i == 2)
		pkt = new AccountPacket(actionLogout, username, password);
	//store packet type at beginning of string
	//memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer );
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;

}
//Action in the lobby room
void CreateChatroom(SOCKET socket, const char* username, const char* roomName)
{
	char TxBuffer[1024] = {};
	Packet* pkt;
	pkt = new ChatroomPacket(actionNewChatroom, roomName, username);
	pkt->GetSerializedData(TxBuffer);
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
}

void JoinChatroom(SOCKET socket, long roomID)
{
	char TxBuffer[1024] = {};
	Packet* pkt = new ChatroomPacket(actionJoinChatroom, roomID);
	pkt->GetSerializedData(TxBuffer);
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
}
void LeaveChatroom(SOCKET socket, long roomID)
{
	char TxBuffer[1024] = {};
	char RxBuffer[1024] = {};

	Packet* pkt = new ChatroomPacket(actionLeaveChatroom, roomID);

	//store packet type at beginning of string
	memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer + typeNameSize);
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;

}

void WelcomWindow(SOCKET ClientSocket)
{
	cout << "Register"; if (cursor == 0) { cout << "<";}cout << endl;
	cout << "Login"; if (cursor == 1) { cout << "<"; }cout << endl;
	DisplayError();

	char usernameBuffer[usernameLength] = {};
	char passwordBuffer[passwordLength] = {};
	int input = 0;
	switch ((input = _getch()))
	{
	case 72://key up
		if (cursor > 0)
			cursor--;
		break;
	case 80://key down
		if (cursor < 1)
			cursor++;
		break;
	case '\r'://enter
		cout << "Enter username:";
		cin >> usernameBuffer;
		cout << "Enter password:";
		cin >> passwordBuffer;
		RegisterLogin(ClientSocket, usernameBuffer, passwordBuffer, cursor);
		break;
	}
	

}
void LobbyWindow(SOCKET ClientSocket)
{
	cout << "Logged in as " << currentUser.username << endl<<endl;
	cout << "Chatrooms:" << endl;
	for (int i = 0; i < chatroomList.size(); i++)
	{
		cout << chatroomList[i].chatroomName;
		if (cursor == i)
			cout << " <";
		cout << endl;
	}
	cout << "------------------------------" << endl;
	DisplayError();
	cout << "CreateChatroom";
	if (cursor == chatroomList.size())
		cout << "<";
	cout << endl << "JoinChatroom";
	if (cursor == chatroomList.size()+1)
		cout << "<";
	cout << endl<<"Sign out";
	if (cursor == chatroomList.size() + 2)
		cout << "<";
	int input = 0;
	switch ((input = _getch()))
	{
		case 72://key up
			if (cursor > 0)
				cursor--;
			break;
		case 80://key down
			if (cursor < chatroomList.size()+2)
				cursor++;
			break;
		case '\r'://enter
			if (cursor >= 0 && cursor < chatroomList.size())
			{
				currentChatroom = chatroomList[cursor];
				cursor = 0;
				currentState = ClientState::Chatroom;
			}
			else if (cursor == chatroomList.size())
			{
				string roomNameBuff;
				cout << "enter room name:";
				getline(cin, roomNameBuff);
				if (roomNameBuff.size() > 0)
					CreateChatroom(ClientSocket, currentUser.username, roomNameBuff.c_str());
			}
			else if (cursor == chatroomList.size()+1)
			{
				long idBuff;
				cout << "enter room id:";
				cin >> idBuff;
				if (idBuff > 0)
					JoinChatroom(ClientSocket, idBuff);
			}
			//sign out
			else if (cursor == chatroomList.size() + 2)
			{
				long idBuff;
				cout << "enter room id:";
				cin >> idBuff;
				if (idBuff > 0)
					JoinChatroom(ClientSocket, idBuff);
				cursor = 0;
				currentState = ClientState::Welcome;
			}
			break;
	}
}
//Chatroom functions
void DisplayMessage(MessageData data)
{
	char time[26] = {};
	struct tm buf;
	localtime_s(&buf, &data.timestamp);
	asctime_s(time, sizeof(time), &buf);
	cout << data.username << "|" << time << endl;
	//cout << data.username << "|"  << endl;
	cout << data.message << endl << endl;
}
//take user inputted message and send over to chatroom
void SendChatMessage(SOCKET socket, char* username, long chatroomID, const char* message)
{
	char TxBuffer[1024] = {};

	Packet* pkt = new MessagePacket(typeMessage, chatroomID, username, message);
	//memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer);
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
\
}
void ChatroomWindow(SOCKET ClientSocket)
{
	cout << "Chatroom:" << currentChatroom.chatroomName<<" #"<<currentChatroom.chatroomID << endl << endl;
	cout << "Members:" << endl;
	for (int i = 0; i < chatroomMemberMap[currentChatroom.chatroomID].size(); i++)
	{
		cout << chatroomMemberMap[currentChatroom.chatroomID][i].username << " ";
	}
	cout << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < chatroomMessageMap[currentChatroom.chatroomID].size(); i++)
	{
		DisplayMessage(chatroomMessageMap[currentChatroom.chatroomID][i]);
	}
	//if(rxFlag==1)
	//	DisplayMessage(singlemsg);
	cout << "----------------------" << endl;
	cout << "Enter message:(enter exit to leave,just click enter to refresh)" << endl;
	string input;
	getline(cin, input);
	if (strncmp(input.c_str(), "exit", 4) == 0)
	{
		currentState = ClientState::Lobby;
		cursor = 0;
	}
	else if (input.length() == 0)
	{

	}
	else
	{
		SendChatMessage(ClientSocket, currentUser.username, currentChatroom.chatroomID, input.c_str());
	}
}

void ClientStateMachine(SOCKET ClientSocket)
{
	while (1)
	{

		switch (currentState)
		{
		case ClientState::Welcome:

			//{
			//	strncpy_s(currentUser, usernameBuffer, usernameLength);
			//	currentState = Lobby;
			//	recvResponse(ClientSocket);
			//	//
			//}
			WelcomWindow(ClientSocket);
			break;
		case ClientState::Lobby:

			LobbyWindow(ClientSocket);
			//cout << "lobbyehre" << endl;
			//getchar();
			break;
		case ClientState::Chatroom:
			ChatroomWindow(ClientSocket);
			break;
		default:
			break;
		}
		system("CLS");
	}
}
/////////////////////////////////Server////////////////////////////////////////
