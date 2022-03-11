#pragma once
#include <iostream>
#include <memory>
#include <iostream>
#include <fstream>
using namespace std;
const int EmptyPktSize = 6;					//Number of data bytes in a packet with no data field
const int usernameLength = 20;
const int passwordLength = 20;
const int typeNameSize = 10;
const int chatroomIDSize = 20;
const int chatroomNameSize = 20;
const int messageLength = 200;
const int responseSize = 20;
class Packet
{
protected:
	struct Header
	{
		char type[typeNameSize];
		int length;
	}head;

public:
	//Safe initialize
	Packet()
	{
		memset(head.type, 0, typeNameSize);
		head.length = 0;
	}
	void SetHeader(char* type)
	{
		memcpy(&head.type, type, typeNameSize);
	}
	char* GetType()
	{
		return head.type;
	}
	int GetLength()
	{
		return 0;
	}

	//print object data on console
	virtual void Print()
	{
		cout << "Packet type:" << head.type << endl;
	}
	//serialize object and store in buffer
	virtual void GetSerializedData(char* buffer)=0;
	void CalculateCRC()
	{

	};
};
