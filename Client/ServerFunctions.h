/*#pragma once
#include <windows.networking.sockets.h>
#include "Packets.h"

#include <vector>
#include <map>
#include <ctime>
void sendFailResponse(SOCKET socket,const char* failmsg)
{
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(failmsg, 0);
	//pkt->GetSerializedData(TxBuffer + typeNameSize);
	pkt->GetSerializedData(TxBuffer);
	//send string over socket
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
}
void sendLogin(SOCKET socket, AccountPacket account)
{
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(respLoginSuccess, 1);

	//memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	//pkt->GetSerializedData(TxBuffer + typeNameSize);
	pkt->GetSerializedData(TxBuffer);
	account.GetSerializedData(TxBuffer + sizeof(HeaderPacket));
	//send string over socket
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
}
//send the member and message data of a chatroom
void sendChatroomInfo(SOCKET socket, long chatroomID)
{
	//member data in database. replace this with data retrieved from database
	vector<AccountData> mockMemberList;
	mockMemberList.push_back({ "user 1","pw1" });
	mockMemberList.push_back({ "user 2","pw2" });
	if(chatroomID==10003)
		mockMemberList.push_back({ "user 3","pw3" });
	/////////////////////////////////////////////////////
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(respMemberList, mockMemberList.size());
	pkt->GetSerializedData(TxBuffer);
	memcpy(TxBuffer + sizeof(HeaderPacket), &chatroomID, sizeof(long));
	for (int i = 0; i < mockMemberList.size(); i++)
	{
		memcpy(TxBuffer + sizeof(HeaderPacket) + sizeof(long) + sizeof(AccountData) * i, &mockMemberList[i], sizeof(AccountData));
	}
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
	//message data in database. replace this with data retrieved from database
	vector<MessageData> mockMessageList;
	mockMessageList.push_back({ "user 1",chatroomID,"test message 1",time(NULL) });
	mockMessageList.push_back({ "user 2",chatroomID,"test message 2",time(NULL) });
	mockMessageList.push_back({ "user 3",chatroomID,"test message 3",time(NULL) });
	if (chatroomID == 10002)
		mockMessageList.push_back({ "user 1",chatroomID,"test message 4",time(NULL) });
	/////////////////////////////////////////////////////
	pkt = new HeaderPacket(respMessageList, mockMessageList.size());
	pkt->GetSerializedData(TxBuffer);
	for (int i = 0; i < mockMessageList.size(); i++)
	{
		memcpy(TxBuffer + sizeof(HeaderPacket) + sizeof(MessageData) * i, &mockMessageList[i], sizeof(MessageData));
	}
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
}

//send a list of all chatrooms the user is in
void sendChatroomList(SOCKET socket, const char* username)
{
	//replace this with data retrieved from database
	vector<ChatroomData> mockChatroomList;
	mockChatroomList.push_back({ "room1","user1",10001});
	mockChatroomList.push_back({ "room2","user2",10002});
	mockChatroomList.push_back({ "room3","user3",10003});
	/////////////////////////////////////////////////////
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(respChatroomList, mockChatroomList.size());
	pkt->GetSerializedData(TxBuffer);
	for (int i = 0; i < mockChatroomList.size(); i++)
	{
		memcpy(TxBuffer + sizeof(HeaderPacket) + sizeof(ChatroomData) * i, &mockChatroomList[i], sizeof(ChatroomData));
	}
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
	//send the member and message data of each chatroom
	for (int i = 0; i < mockChatroomList.size(); i++)
	{
		sendChatroomInfo(socket, mockChatroomList[i].chatroomID);
	}
}
//create a new chatroom in database and store data in dest.
void CreateChatroom(SOCKET socket, const char* chatroomName, const char* username)
{

	//create a room entry in database and store data here
	ChatroomData mockRoom = { "testCreateRoom","someUser",10000 + rand()};
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(respChatroomList, 1);
	pkt->GetSerializedData(TxBuffer);
	memcpy(TxBuffer + sizeof(HeaderPacket), &mockRoom, sizeof(ChatroomData));
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	sendChatroomInfo(socket, mockRoom.chatroomID);
}
//return false if no matching chatroom found, otherwise store chatroom data in dest
void JoinChatroom(SOCKET socket, long chatroomID)
{
	//return fa
	if (chatroomID == 10004)
	{
		ChatroomData mockRoom = { "testJoinRoom","someUser",10004 };
		char TxBuffer[1024] = {};
		Packet* pkt = new HeaderPacket(respChatroomList, 1);
		pkt->GetSerializedData(TxBuffer);
		memcpy(TxBuffer + sizeof(HeaderPacket), &mockRoom, sizeof(ChatroomData));
		send(socket, TxBuffer, sizeof(TxBuffer), 0);
		sendChatroomInfo(socket, 10004);
	}
	else
	{
		sendFailResponse(socket, respJoinRoomFail);
	}
}
//store a message into the chatroom message table in database
void StoreMessage(MessagePacket msgPkt)
{

}
//send a message to every connected socket where the logged in user is in the chatroom
void RelayMessage(SOCKET socket,MessagePacket msgPkt)
{
	char TxBuffer[1024] = {};
	Packet* header = new HeaderPacket(respMessageList, 1);
	header->GetSerializedData(TxBuffer);
	MessageData msgBuf = msgPkt.GetMessageData();
	memcpy(TxBuffer + sizeof(HeaderPacket), &msgBuf, sizeof(MessageData));
	//msgPkt.GetSerializedData(TxBuffer+sizeof(HeaderPacket));
	msgPkt.Print();
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
}


bool VerifyRegister(const char* username, const char* password)
{
	return true;
}
bool VerifyLogin(const char* username, const char* password)
{
	return true;
}

bool RecvClientPacket(SOCKET ConnectionSocket)
{
	char RxBuffer[1024] = {};
	char RxPacketType[typeNameSize] = {};
		if(recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0)<=0)
			return false;
		//cout << RxBuffer << endl;
		memcpy(RxPacketType, RxBuffer, typeNameSize);

		//received register and login
		if (memcmp(RxPacketType, typeAccount, typeNameSize) == 0)
		{
			//rxPkt = new AccountPacket(RxBuffer + typeNameSize);
			//rxPkt->Print();
			char Buffer[sizeof(AccountPacket)] = {};
			memcpy(Buffer, RxBuffer, sizeof(AccountPacket));
			AccountPacket rxPkt(Buffer);
			rxPkt.Print();
			if (VerifyLogin(rxPkt.GetUsername(), rxPkt.GetPassword()))
			{
				sendLogin(ConnectionSocket, rxPkt);
				sendChatroomList(ConnectionSocket, rxPkt.GetUsername());
			}
			else
			{
				sendFailResponse(ConnectionSocket, respLoginFail);
			}
		}
		//received chatroom request
		else if (memcmp(RxPacketType, typeChatroom, typeNameSize) == 0)
		{
			char Buffer[sizeof(ChatroomPacket)] = {};
			memcpy(Buffer, RxBuffer, sizeof(ChatroomPacket));
			ChatroomPacket rxRoomPkt(Buffer);
			//rxRoomPkt.Print();
			//new room
			if (strncmp(rxRoomPkt.GetAction(), actionNewChatroom, typeNameSize) == 0)
			{
				rxRoomPkt.Print();
				CreateChatroom(ConnectionSocket, rxRoomPkt.GetChatroomName(), rxRoomPkt.GetOwnerName());
			}
			//join room
			if (strncmp(rxRoomPkt.GetAction(), actionJoinChatroom, typeNameSize) == 0)
			{
				rxRoomPkt.Print();
				JoinChatroom(ConnectionSocket, rxRoomPkt.GetChatroomID());
			}
			//leave room
			if (strncmp(rxRoomPkt.GetAction(), actionLeaveChatroom, typeNameSize) == 0)
			{

			}
		}
		//received chat message
		else if (memcmp(RxPacketType, typeMessage, typeNameSize) == 0)
		{
			//rxPkt = new AccountPacket(RxBuffer + typeNameSize);
			//rxPkt->Print();
			char Buffer[sizeof(MessagePacket)] = {};
			memcpy(Buffer, RxBuffer, sizeof(MessagePacket));
			MessagePacket rxMsgPkt(Buffer);
			//rxMsgPkt.Print();
			StoreMessage(rxMsgPkt);
			RelayMessage(ConnectionSocket, rxMsgPkt);
		}
		return true;

}*/