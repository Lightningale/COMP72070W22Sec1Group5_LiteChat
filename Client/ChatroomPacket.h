#pragma once
#include "Packet.h"
class ChatroomPacket :public Packet
{
	struct ChatroomData
	{
		char actionType[typeNameSize];
		char chatroomID[chatroomIDSize];
		char chatroomName[chatroomNameSize];
	}chatroomData;

public:
	ChatroomPacket(char* src)
	{
		memcpy(&head, src, sizeof(Header));
		memcpy(&chatroomData, src + sizeof(Header), sizeof(ChatroomData));
	}
	ChatroomPacket(char* actionType, char* chatroomID, char* chatroomName)
	{
		memcpy(chatroomData.actionType, actionType, typeNameSize);
		memcpy(chatroomData.chatroomID, chatroomID, chatroomIDSize);
		memcpy(chatroomData.chatroomName, chatroomName, chatroomNameSize);
	}
	//serialize object and store in buffer
	void GetSerializedData(char* buffer)
	{
		memcpy(buffer, &head, sizeof(Header));
		memcpy(buffer + sizeof(Header), &chatroomData, sizeof(ChatroomData));
	}
	char* GetActionType()
	{
		return chatroomData.actionType;
	}
	char* GetChatroomName()
	{
		return chatroomData.chatroomName;
	}
	char* GetChatroomID()
	{
		return chatroomData.chatroomID;
	}
	void Print()
	{
		cout << "Packet type:" << head.type << endl;
		cout << "Action:" << chatroomData.actionType << endl;
		cout << "Chatroom ID:" << chatroomData.chatroomID << endl;
		cout << "Chatroom Name:" << chatroomData.chatroomName << endl;
	}
};