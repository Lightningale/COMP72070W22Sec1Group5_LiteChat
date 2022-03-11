#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Packets.h"
using namespace std;

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
	char TxBuffer[1024] = {};
	Packet* pkt;
	char packetType[typeNameSize] = "Account";
	char actionType[typeNameSize] = "login";
	char username[usernameLength] = "Geyang";
	char password[passwordLength] = "GeyangPassword";
	pkt = new AccountPacket(actionType,username,password);
	pkt->SetHeader(packetType);
	//store packet type at beginning of string
	memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	pkt->GetSerializedData(TxBuffer + typeNameSize);
	cout << TxBuffer << endl;
	send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
	//closes connection and socket
	closesocket(ClientSocket);

	//frees Winsock DLL resources
	WSACleanup();

	return 1;
}
