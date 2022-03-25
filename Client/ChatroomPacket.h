#pragma once
#include "Packet.h"
struct ChatroomData
{
	//char actionType[typeNameSize];
	char chatroomName[chatroomNameSize];
	char owner[usernameLength];
	long chatroomID;
};
class ChatroomPacket :public Packet
{
	ChatroomData chatroomData;

public:
	ChatroomPacket(char* src)
	{
		memcpy(&head, src, sizeof(Header));
		memcpy(&chatroomData, src + sizeof(Header), sizeof(ChatroomData));
	}

	//Constructor that takes room name and username for creating new room
	ChatroomPacket(const char* actionType, const char* chatroomName, const char* ownerName)
	{
		//memcpy(chatroomData.actionType, actionType, typeNameSize);
		memcpy(chatroomData.chatroomName, chatroomName, chatroomNameSize);
		memcpy(chatroomData.owner, ownerName, chatroomNameSize);
		this->SetHeader(typeChatroom,actionType);
	}
	//Constructor that takes room id for join or leave room
	ChatroomPacket(const char* actionType, long roomID)
	{
		//memcpy(chatroomData.actionType, actionType, typeNameSize);
		chatroomData.chatroomID = roomID;
		this->SetHeader(typeChatroom,actionType);
	}
	void SetRoomName(const char* chatroomName)
	{
		memcpy(chatroomData.chatroomName, chatroomName, chatroomNameSize);
	}
	void SetOwnerName(const char* ownerName)
	{
		memcpy(chatroomData.owner, ownerName, chatroomNameSize);
	}
	void SetActionType(const char* actionType)
	{
		this->SetHeader(typeChatroom, actionType);
	}
	void SetRoomID(long id)
	{
		chatroomData.chatroomID = id;
	}
	//serialize object and store in buffer
	void GetSerializedData(char* buffer)
	{
		memcpy(buffer, &head, sizeof(Header));
		memcpy(buffer + sizeof(Header), &chatroomData, sizeof(ChatroomData));
	}
	char* GetActionType()
	{
		return head.action;
	}
	char* GetChatroomName()
	{
		return chatroomData.chatroomName;
	}
	ChatroomData GetChatroomData()
	{
		return chatroomData;
	}
	long GetChatroomID()
	{
		return chatroomData.chatroomID;
	}
	void Print()
	{
		cout << "Packet type:" << head.type << endl;
		cout << "Action:" << head.action << endl;
		cout << "Chatroom ID:" << chatroomData.chatroomID << endl;
		cout << "Chatroom Name:" << chatroomData.chatroomName << endl;
		cout << "Chatroom Owner:" << chatroomData.owner << endl;
	}
};