#pragma once
#include <windows.networking.sockets.h>
#include "Packets.h"
//Client
enum ClientState { Welcome, Lobby, Chatroom };

//receive response from server, return true if server responses success, return false if otherwise
bool recvResponse(SOCKET socket)
{
	char RxBuffer[1024] = {};
	recv(socket, RxBuffer, sizeof(RxBuffer), 0);
	char RxPacketType[typeNameSize] = {};
	memcpy(RxPacketType, RxBuffer, typeNameSize);
	if (memcmp(RxPacketType, typeResponse, typeNameSize) == 0)
	{
		char Buffer[sizeof(ResponsePacket)] = {};
		memcpy(Buffer, RxBuffer + typeNameSize, sizeof(ResponsePacket));
		ResponsePacket rxPkt(Buffer);
		rxPkt.Print();
		if (strncmp(rxPkt.getResponse(), responseSuccess, responseSize) == 0)
		{
			return true;
		}
	}
	return false;
}
//Last parameter defines whether it's register or login action. Return true if action succeeded
bool RegisterLogin(SOCKET socket, char* username,char* password, int i)
{
	char TxBuffer[1024] = {};
	char RxBuffer[1024] = {};
	Packet* pkt;
	if (i == 0)
		pkt = new AccountPacket(actionRegister, username, password);
	else
		pkt = new AccountPacket(actionLogin, username, password);
	//store packet type at beginning of string
	memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer + typeNameSize);
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
	if (recvResponse(socket))
	{
		//strncpy(username, usernameBuffer, usernameLength);
		
		//currentState = Main;
		return true;
	}
	else
	{
		cout << "Register/Login failed" << endl;
		return false;
	}
}
//Action in the lobby room
void LobbyRoom()
{

}
bool CreateChatroom(SOCKET socket, char* username, char* roomName)
{
	char TxBuffer[1024] = {};
	char RxBuffer[1024] = {};

	Packet* pkt;
		pkt = new ChatroomPacket(actionNewChatroom, roomName, username);
	//store packet type at beginning of string
	memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer + typeNameSize);
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
	if (recvResponse(socket))
	{
		return true;
	}
	else
	{
		cout << "Action failed" << endl;
		return false;
	}
}

bool JoinChatroom(SOCKET socket, long roomID)
{
	char TxBuffer[1024] = {};
	char RxBuffer[1024] = {};

	Packet* pkt= new ChatroomPacket(actionJoinChatroom, roomID);

	//store packet type at beginning of string
	memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer + typeNameSize);
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
	if (recvResponse(socket))
	{
		return true;
	}
	else
	{
		cout << "Action failed" << endl;
		return false;
	}
}
bool LeaveChatroom(SOCKET socket, long roomID)
{
	char TxBuffer[1024] = {};
	char RxBuffer[1024] = {};

	Packet* pkt = new ChatroomPacket(actionLeaveChatroom, roomID);

	//store packet type at beginning of string
	memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer + typeNameSize);
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
	if (recvResponse(socket))
	{
		return true;
	}
	else
	{
		cout << "Action failed" << endl;
		return false;
	}
}
//take user inputted message and send over to chatroom
bool SendChatMessage(SOCKET socket, char* username, long chatroomID)
{
	char TxBuffer[1024] = {};
	char RxBuffer[1024] = {};
	char message[messageLength] = {};
	cin >> message;
	Packet* pkt = new MessagePacket(typeMessage, chatroomID, username, message);
	memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer + typeNameSize);
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
	return recvResponse(socket);
}

/////////////////////////////////Server////////////////////////////////////////
void sendResponse(SOCKET socket, bool response)
{
	char TxBuffer[1024] = {};
	Packet* pkt;
	if (response)
		pkt = new ResponsePacket(responseSuccess);
	else
		pkt = new ResponsePacket(responseFail);
	memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer + typeNameSize);
	//send string over socket
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
}
bool VerifyRegister()
{
	return true;
}
bool VerifyLogin()
{
	return true;
}