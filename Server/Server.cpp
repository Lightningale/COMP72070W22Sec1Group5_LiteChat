#include <windows.networking.sockets.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include "ServerSend.h"
#include "../Client/Packets.h"
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
	//Packet* rxPkt;
	char RxBuffer[1024] = {};
	char PacketType[typeNameSize] = "Account";
	char RxPacketType[typeNameSize] = {};
	recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
	cout << RxBuffer << endl;
	memcpy(RxPacketType, RxBuffer, typeNameSize);
	if (memcmp(RxPacketType, PacketType, typeNameSize) == 0)
	{
		//rxPkt = new AccountPacket(RxBuffer + typeNameSize);
		//rxPkt->Print();
		char Buffer[sizeof(AccountPacket)] = {};
		memcpy(Buffer, RxBuffer + typeNameSize, sizeof(AccountPacket));
		AccountPacket rxPkt(Buffer);
		rxPkt.Print();
	}
		






	closesocket(ConnectionSocket);	//closes incoming socket
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();					//frees Winsock resources

	getchar();

	return 1;
}