#pragma once
#include <iostream>
#include <memory>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
const int EmptyPktSize = 6;					//Number of data bytes in a packet with no data field
const int usernameLength = 20;
const int passwordLength = 20;
const int typeNameSize = 10;
const int chatroomIDSize = 20;
const int chatroomNameSize = 20;
const int messageLength = 200;
const int responseSize = 20;
const char typeAccount[typeNameSize] = "Account";
const char typeChatroom[typeNameSize] = "Chatroom";
const char typeMessage[typeNameSize] = "Message";
const char typeResponse[typeNameSize] = "Response";
const char actionRegister[typeNameSize] = "Register";
const char actionLogin[typeNameSize] = "Login";
const char actionEnterChatroom[typeNameSize] = "EnterRoom";
const char actionNewChatroom[typeNameSize] = "NewRoom";
const char actionJoinChatroom[typeNameSize] = "JoinRoom";
const char actionLeaveChatroom[typeNameSize] = "LeaveRoom";
const char roomData[typeNameSize] = "RoomData";
const char responseSuccess[responseSize] = "Success";
const char respRegisterFail[responseSize] = "RegisterFail";
const char respLoginFail[responseSize] = "LoginFail";
const char respCreateRoomFail[responseSize] = "CreateRoomFail";
const char respJoinRoomFail[responseSize] = "JoinRoomFail";
const char respRegisterSuccess[responseSize] = "RegisterSuccess";
const char respLoginSuccess[responseSize] = "LoginSuccess";
const char createRoomSuccess[responseSize] = "CreateRoomSuccess";
const char respChatroomList[responseSize] = "ChatroomList";
const char respMemberList[responseSize] = "MemberList";
const char respMessageList[responseSize] = "MessageList";
const char errRegister[messageLength] = "Username taken";
const char errLogin[messageLength] = "Wrong username or password";
class Packet
{
protected:
	struct Header
	{
		char type[typeNameSize];
		char action[typeNameSize];
		int size;
		time_t timestamp;
	}head;

public:
	//Safe initialize
	Packet()
	{
		memset(head.type, 0, typeNameSize);
		head.size = sizeof(head);
		head.timestamp = time(NULL);
	}
	void SetHeader(const char* type,const char* action)
	{
		memcpy(&head.type, type, typeNameSize);
		memcpy(&head.action, action, typeNameSize);
	}
	char* GetType()
	{
		return head.type;
	}
	char* GetAction()
	{
		return head.action;
	}
	int GetLength()
	{
		return 0;
	}
	time_t GetTime()
	{
		return head.timestamp;
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
