#pragma once
#include "Packet.h"
class MessagePacket :public Packet
{
	struct MessageData
	{
		char actionType[typeNameSize];
		char chatroomID[chatroomIDSize];
		char username[usernameLength];
		char message[messageLength];
	}messageData;

public:
	MessagePacket(char* src)
	{
		memcpy(&head, src, sizeof(Header));
		memcpy(&messageData, src + sizeof(Header), sizeof(MessageData));
	}
	MessagePacket(char* actionType, char* chatroomID, char* username,char* message)
	{
		memcpy(messageData.actionType, actionType, typeNameSize);
		memcpy(messageData.chatroomID, chatroomID, chatroomIDSize);
		memcpy(messageData.username, username, usernameLength);
		memcpy(messageData.message, message, messageLength);
	}
	//serialize object and store in buffer
	void GetSerializedData(char* buffer)
	{
		memcpy(buffer, &head, sizeof(Header));
		memcpy(buffer + sizeof(Header), &messageData, sizeof(MessageData));
	}
	char* getActionType()
	{
		return messageData.actionType;
	}
	char* Getusername()
	{
		return messageData.username;
	}
	char* getChatroomID()
	{
		return messageData.chatroomID;
	}
	void Print()
	{
		cout << "Packet type:" << head.type << endl;
		cout << "Action:" << messageData.actionType << endl;
		cout << "Chatroom ID:" << messageData.chatroomID << endl;
		cout << "User Name:" << messageData.username << endl;
		cout << "Message:" << messageData.message << endl;
	}
};