#pragma once
#include "Packet.h"
class AccountPacket :public Packet
{
	struct AccountData
	{
		char actionType[typeNameSize];
		char username[usernameLength];
		char password[passwordLength];
	}accountData;

public:
	AccountPacket(char* src)
	{
		memcpy(&head, src, sizeof(Header));
		memcpy(&accountData, src + sizeof(Header), sizeof(AccountData));
	}
	AccountPacket(char* actionType, char* username, char* password)
	{
		memcpy(accountData.actionType, actionType, typeNameSize);
		memcpy(accountData.username, username, usernameLength);
		memcpy(accountData.password, password, passwordLength);
	}
	//serialize object and store in buffer
	void GetSerializedData(char* buffer)
	{
		memcpy(buffer, &head, sizeof(Header));
		memcpy(buffer + sizeof(Header), &accountData, sizeof(AccountData));
	}
	char* GetActionType()
	{
		return accountData.actionType;
	}
	char* GetUserName()
	{
		return accountData.username;
	}
	char* GetPassword()
	{
		return accountData.password;
	}
	void Print()
	{
		cout << "Packet type:" << head.type << endl;
		cout << "Action:" << accountData.actionType << endl;
		cout << "Username:" << accountData.username << endl;
		cout << "Password:" << accountData.password << endl;
	}
};