#include <windows.networking.sockets.h>
#include <iostream>
#include <string>
#include "../Client/ServerFunctions.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main()
{
	//starts Winsock DLLs		
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	//create server socket
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//binds socket to address
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = INADDR_ANY;
	SvrAddr.sin_port = htons(27000);
	if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	{
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	//listen on a socket
	if (listen(ServerSocket, 1) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}


	cout << "Waiting for client connection\n" << endl;

	//accepts a connection from a client
	SOCKET ConnectionSocket;
	ConnectionSocket = SOCKET_ERROR;
	if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	cout << "Connection Established" << endl;
	/////////////////////////////////////////
	// 
	
	//Packet* rxPkt;
	
	char RxBuffer[1024] = {};
	char RxPacketType[typeNameSize] = {};
	while (1)

	{
		recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
		//cout << RxBuffer << endl;
		memcpy(RxPacketType, RxBuffer, typeNameSize);

		//received register and login
		if (memcmp(RxPacketType, typeAccount, typeNameSize) == 0)
		{
			//rxPkt = new AccountPacket(RxBuffer + typeNameSize);
			//rxPkt->Print();
			char Buffer[sizeof(AccountPacket)] = {};
			memcpy(Buffer, RxBuffer, sizeof(AccountPacket));
			AccountPacket rxPkt(Buffer);
			rxPkt.Print();
			if (VerifyLogin(rxPkt.GetUsername(), rxPkt.GetPassword()))
			{
				sendLogin(ConnectionSocket, rxPkt);
				sendChatroomList(ConnectionSocket, rxPkt.GetUsername());
			}
			else
			{
				senFailResponse(ConnectionSocket, respLoginFail);
			}
		}
		//received chat message
		else if (memcmp(RxPacketType, typeMessage, typeNameSize) == 0)
		{
			//rxPkt = new AccountPacket(RxBuffer + typeNameSize);
			//rxPkt->Print();
			char Buffer[sizeof(MessagePacket)] = {};
			memcpy(Buffer, RxBuffer, sizeof(MessagePacket));
			MessagePacket rxMsgPkt(Buffer);
			//rxMsgPkt.Print();
			StoreMessage(rxMsgPkt);
			RelayMessage(ConnectionSocket, rxMsgPkt);
		}
	}
	//






	closesocket(ConnectionSocket);	//closes incoming socket
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();					//frees Winsock resources

	getchar();

	return 1;
}
