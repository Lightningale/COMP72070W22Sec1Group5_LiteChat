#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Packet.h"

class MessagePacket :public Packet
{
	struct MessageData
	{
		//char actionType[typeNameSize];
		char username[usernameLength];
		long chatroomID;
		char message[messageLength];
	}messageData;

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
		this->SetHeader(typeMessage,actionType);
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
	void Print()
	{
		/*cout << "Packet type:" << head.type << endl;
		cout << "Action:" << messageData.actionType << endl;
		cout << "Chatroom ID:" << messageData.chatroomID << endl;
		cout << "User Name:" << messageData.username << endl;
		cout << "Message:" << messageData.message << endl;*/
		char time[26] = {};
		struct tm buf;
		localtime_s(&buf, &this->head.timestamp);
		asctime_s(time, sizeof(time), &buf);
		//cout << messageData.username << "|" << asctime(localtime(&this->head.timestamp)) << endl;
		cout << messageData.username << "|" << time << endl;
		cout << messageData.message << endl << endl;
	}
};