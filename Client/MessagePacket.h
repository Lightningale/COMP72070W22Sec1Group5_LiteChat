#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Packet.h"
struct MessageData
{
	//char actionType[typeNameSize];
	char username[usernameLength];
	long chatroomID;
	char message[messageLength];
	time_t timestamp;
};
class MessagePacket :public Packet
{
	MessageData messageData;

public:
	MessagePacket(char* src)
	{
		memcpy(&head, src, sizeof(Header));
		memcpy(&messageData, src + sizeof(Header), sizeof(MessageData));
	}
	MessagePacket(const char* actionType, const long chatroomID, const char* username,const char* message)
	{
		//memcpy(messageData.actionType, actionType, typeNameSize);
		memcpy(messageData.username, username, usernameLength);
		messageData.chatroomID = chatroomID;
		memcpy(messageData.message, message, messageLength);
		messageData.timestamp = head.timestamp;
		this->SetHeader(typeMessage,actionType);
		head.size += sizeof(MessageData);
	}
	//serialize object and store in buffer
	void GetSerializedData(char* buffer)
	{
		memcpy(buffer, &head, sizeof(Header));
		memcpy(buffer + sizeof(Header), &messageData, sizeof(MessageData));
	}
	char* getActionType()
	{
		return head.action;
	}
	char* Getusername()
	{
		return messageData.username;
	}
	long getChatroomID()
	{
		return messageData.chatroomID;
	}
	MessageData GetMessageData()
	{
		return messageData;
	}
	void Print()
	{

	//	char time[26] = {};
	//	struct tm buf;
	//	localtime_s(&buf, &messageData.timestamp);
	//	asctime_s(time, sizeof(time), &buf);
		//cout << messageData.username << "|" << asctime(localtime(&this->head.timestamp)) << endl;
		cout << messageData.username << "|" <<"at room "<<messageData.chatroomID << endl;
		cout << messageData.message << endl << endl;
	}
};