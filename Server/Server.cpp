#include <windows.networking.sockets.h>
#include <iostream>
#include <string>
#include "Database.h"
#include "../Client/Packets.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main()
{
	// Start connection with SQL database
	sql::Connection* connection;
	connection = DB_CONNECT();

	// Create table for users 
	DB_CREATE_USER_TABLE(connection);

	// Create table for chatrooms
	DB_CREATE_CHATROOM_TABLE(connection);

	// Create table for messages
	DB_CREATE_MESSAGE_TABLE(connection);

	// Create table for rooms that users are joined in
	DB_CREATE_USER_ROOM_TABLE(connection, "cheshirecat");

	DB_CREATE_CHATROOM_USERS_TABLE(connection, "studygroup");

	// Insert a user into users table 
	DB_INSERT_INTO_USERS(connection, "cheshirecat", "zulu", 444);
	DB_INSERT_INTO_USERS(connection, "orangeblackbox", "delta", 654);
	
	//Insert a chatroom into chatrooms table
	DB_INSERT_INTO_CHATROOMS(connection, "study group", "orangeblackbox", 762);

	// Checks for the username in the users table
	DB_CHECK_USER(connection, "cheshirecat");

	// Remove user from database
	DB_REMOVE_USER(connection, "cheshirecat");


	// Ends connection with SQL database
	delete connection;


	////starts Winsock DLLs		
	//WSADATA wsaData;
	//if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	//	return 0;

	////create server socket
	//SOCKET ServerSocket;
	//ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//if (ServerSocket == INVALID_SOCKET) {
	//	WSACleanup();
	//	return 0;
	//}

	////binds socket to address
	//sockaddr_in SvrAddr;
	//SvrAddr.sin_family = AF_INET;
	//SvrAddr.sin_addr.s_addr = INADDR_ANY;
	//SvrAddr.sin_port = htons(27000);
	//if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	//{
	//	closesocket(ServerSocket);
	//	WSACleanup();
	//	return 0;
	//}

	////listen on a socket
	//if (listen(ServerSocket, 1) == SOCKET_ERROR) {
	//	closesocket(ServerSocket);
	//	WSACleanup();
	//	return 0;
	//}


	//cout << "Waiting for client connection\n" << endl;

	////accepts a connection from a client
	//SOCKET ConnectionSocket;
	//ConnectionSocket = SOCKET_ERROR;
	//if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == SOCKET_ERROR) {
	//	closesocket(ServerSocket);
	//	WSACleanup();
	//	return 0;
	//}

	//cout << "Connection Established" << endl;
	///////////////////////////////////////////
	////Packet* rxPkt;
	//char RxBuffer[1024] = {};
	//char PacketType[typeNameSize] = "Account";
	//char RxPacketType[typeNameSize] = {};
	//recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
	//cout << RxBuffer << endl;
	//memcpy(RxPacketType, RxBuffer, typeNameSize);
	//if (memcmp(RxPacketType, PacketType, typeNameSize) == 0)
	//{
	//	//rxPkt = new AccountPacket(RxBuffer + typeNameSize);
	//	//rxPkt->Print();
	//	char Buffer[sizeof(AccountPacket)] = {};
	//	memcpy(Buffer, RxBuffer + typeNameSize, sizeof(AccountPacket));
	//	AccountPacket rxPkt(Buffer);
	//	rxPkt.Print();
	//}
	//	


	//closesocket(ConnectionSocket);	//closes incoming socket
	//closesocket(ServerSocket);	    //closes server socket	
	//WSACleanup();					//frees Winsock resources

	//getchar();

	return 1;
}