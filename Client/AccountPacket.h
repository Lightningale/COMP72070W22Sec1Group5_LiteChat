#pragma once
#include "Packet.h"
struct AccountData
{
	//char actionType[typeNameSize];
	char username[usernameLength];
	char password[passwordLength];
};
class AccountPacket :public Packet
{
	AccountData accountData;

public:
	AccountPacket(char* src)
	{
		memcpy(&head, src, sizeof(Header));
		memcpy(&accountData, src + sizeof(Header), sizeof(AccountData));
	}
	AccountPacket(const char* actionType, const char* username, const char* password)
	{
		//memcpy(accountData.actionType, actionType, typeNameSize);
		memcpy(accountData.username, username, usernameLength);
		memcpy(accountData.password, password, passwordLength);
		this->SetHeader(typeAccount,actionType);
		head.size += sizeof(AccountData);
	}
	//serialize object and store in buffer
	void GetSerializedData(char* buffer)
	{
		memcpy(buffer, &head, sizeof(Header));
		memcpy(buffer + sizeof(Header), &accountData, sizeof(AccountData));
	}
	char* GetActionType()
	{
		return head.action;
	}
	char* GetUsername()
	{
		return accountData.username;
	}
	char* GetPassword()
	{
		return accountData.password;
	}
	AccountData GetAccountData()
	{
		return accountData;
	}

	void Print()
	{
		cout << "Packet type:" << head.type << endl;
		cout << "Action:" << head.action << endl;
		cout << "Username:" << accountData.username << endl;
		cout << "Password:" << accountData.password << endl;
	}
};