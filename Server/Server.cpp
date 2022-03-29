#include <windows.networking.sockets.h>
#include <stdint.h> 
#include <iostream>
#include <string>
#include "ServerFunctions.h"
]
#pragma comment(lib, "Ws2_32.lib")

#define MAXCLIENTS 30
using namespace std;

int main()
{
	// Start connection with SQL database
	sql::Connection* DBconnection;
	DBconnection = DB_CONNECT();


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

	/////////////Multiplexing code/////////////////
	int opt = TRUE;
	int addrlen;
	int max_sd,sd,activity, new_socket,valread;
	SOCKET ClientSocket[MAXCLIENTS] = { 0 };
	fd_set readFDS;
	//set master socket to allow multiple connections , 
	//this is just a good habit, it will work without this 
	if (setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt,
		sizeof(opt)) < 0)
	{
		perror("setsockopt");
		WSACleanup();
		return 0;
	}

	///////////////////////////////////////

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
	addrlen = sizeof(SvrAddr);
	


	cout << "Waiting for client connections\n" << endl;

	/// <summary>
	/// new code
	/// </summary>
	/// <returns></returns>
	while (1)
	{
		//clear the socket set 
		FD_ZERO(&readFDS);

		//add master socket to set 
		FD_SET(ServerSocket, &readFDS);
		max_sd = ServerSocket;

		//add child sockets to set 
		for (int i = 0; i < MAXCLIENTS; i++)
		{
			//socket descriptor 
			sd = ClientSocket[i];

			//if valid socket descriptor then add to read list 
			if (sd > 0)
				FD_SET(sd, &readFDS);

			//highest file descriptor number, need it for the select function 
			if (sd > max_sd)
				max_sd = sd;
		}
		//wait for an activity on one of the sockets , timeout is NULL , 
		//so wait indefinitely 
		activity = select(max_sd + 1, &readFDS, NULL, NULL, NULL);

		if ((activity < 0) && (errno != EINTR))
		{
			printf("select error");
		}

		//If something happened on the master socket , 
		//then its an incoming connection 
		if (FD_ISSET(ServerSocket, &readFDS))
		{
			/*if ((new_socket = accept(ServerSocket, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}*/
			//new_socket=SOCKET_ERROR;
			if ((new_socket = accept(ServerSocket,(struct sockaddr*)&SvrAddr, (int*)&addrlen)) < 0)
			{
				perror("accept");
				closesocket(ServerSocket);
				WSACleanup();
				return 0;
			}

			//inform user of socket number - used in send and receive commands 
			printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(SvrAddr.sin_addr) , ntohs(SvrAddr.sin_port));

			//send new connection greeting message 
			//if (send(new_socket, message, strlen(message), 0) != strlen(message))
		//	{
		//		perror("send");
			//}

			//puts("Welcome message sent successfully");

			//add new socket to array of sockets 
			for (int i = 0; i < MAXCLIENTS; i++)
			{
				//if position is empty 
				if (ClientSocket[i] == 0)
				{
					ClientSocket[i] = new_socket;
					printf("Adding to list of sockets as %d\n", i);

					break;
				}
			}
		}

		//else its some IO operation on some other socket
		for (int i = 0; i < MAXCLIENTS; i++)
		{
			sd = ClientSocket[i];

			if (FD_ISSET(sd, &readFDS))
			{
				//Check if it was for closing , and also read the 
				//incoming message 
				if (!RecvClientPacket(sd))
				{
					//Somebody disconnected , get his details and print 
					getpeername(sd, (struct sockaddr*)&SvrAddr,(int *)&addrlen);
					printf("Host disconnected , ip %s , port %d \n",
						inet_ntoa(SvrAddr.sin_addr), ntohs(SvrAddr.sin_port));

					//Close the socket and mark as 0 in list for reuse 
					closesocket(sd);
					ClientSocket[i] = 0;
				}

			}
		}
	}
	/////////////////////////////////////Old Code////////////////////////////////////

	/*//accepts a connection from a client
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
				sendFailResponse(ConnectionSocket, respLoginFail);
			}
		}
		//received chatroom request
		else if (memcmp(RxPacketType, typeChatroom, typeNameSize) == 0)
		{
			char Buffer[sizeof(ChatroomPacket)] = {};
			memcpy(Buffer, RxBuffer, sizeof(ChatroomPacket));
			ChatroomPacket rxRoomPkt(Buffer);
			//rxRoomPkt.Print();
			//new room
			if (strncmp(rxRoomPkt.GetAction(), actionNewChatroom, typeNameSize) == 0)
			{
				rxRoomPkt.Print();
				CreateChatroom(ConnectionSocket, rxRoomPkt.GetChatroomName(),rxRoomPkt.GetOwnerName());
			}
			//join room
			if (strncmp(rxRoomPkt.GetAction(), actionJoinChatroom, typeNameSize) == 0)
			{
				rxRoomPkt.Print();
				JoinChatroom(ConnectionSocket, rxRoomPkt.GetChatroomID());
			}
			//leave room
			if (strncmp(rxRoomPkt.GetAction(), actionLeaveChatroom, typeNameSize) == 0)
			{

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
	}*/
	//






	//closesocket(ConnectionSocket);	//closes incoming socket
	delete DBconnection;
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();					//frees Winsock resources

	getchar();

	return 1;
}
