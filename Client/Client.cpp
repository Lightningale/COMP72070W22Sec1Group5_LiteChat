#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
//#include "Packets.h"
#include "NetworkFunctions.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;


//enum ClientState{Welcome,Main,Chatroom};

int main()
{
	
	//starts Winsock DLLs
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return 0;
	}

	//initializes socket. SOCK_STREAM: TCP
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}
	///////////////////////////////////
	ClientState currentState = Welcome;
	char currentUser[usernameLength] = "";
	ChatroomData currentChatroom = {0};
	vector<ChatroomData> chatroomList;
	char usernameBuffer[usernameLength] = {};
	char passwordBuffer[passwordLength] = {};
	while (1)
	{
		
		switch (currentState)
		{
		case Welcome:
			cout << "Login/Register" << endl;
			cout << "Enter username:";
			cin >> usernameBuffer;
			cout << "Enter password:";
			cin >> passwordBuffer;
			if (RegisterLogin(ClientSocket, usernameBuffer,passwordBuffer, 0))
			{
				strncpy_s(currentUser, usernameBuffer, usernameLength);
				currentState = Lobby;
				//
			}

			break;
		case Lobby:
			cout << "Logged in as " << usernameBuffer << endl;
			break;
		case Chatroom:

			break;
		default:
			break;
		}
		system("CLS");
	}
	//closes connection and socket
	closesocket(ClientSocket);

	//frees Winsock DLL resources
	WSACleanup();

	return 1;
}
