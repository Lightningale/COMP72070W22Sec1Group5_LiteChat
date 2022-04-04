#include <windows.networking.sockets.h>
#include <stdint.h> 
#include <iostream>
#include <string>
#include "ServerFunctions.h"
#include "ServerSend.h"
#pragma comment(lib, "Ws2_32.lib")

#define MAXCLIENTS 30
using namespace std;

int main()
{
	// Start connection with SQL database
	sql::Connection* DBconnection;
	DBconnection = DB_CONNECT();
	string newLog;

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
	


	//cout << "Waiting for client connections\n" << endl;
	serverLog.push_back(string("Waiting for client connections\n"));
	currentServerState = ServerState::Idle;
	//cout << serverLog[serverLog.size() - 1];
	/// <summary>
	/// new code
	/// </summary>
	/// <returns></returns>
	while (1)
	{
		ServerDisplay();
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
			//printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(SvrAddr.sin_addr) , ntohs(SvrAddr.sin_port));
			serverLog.push_back(string("New connection , socket fd is ")+to_string(new_socket)+string(" ,ip is: ")+ inet_ntoa(SvrAddr.sin_addr)+string(",port: ")+to_string(ntohs(SvrAddr.sin_port))+"\n");
			//cout << serverLog[serverLog.size() - 1];
			currentServerState = ServerState::Waiting;
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
					//printf("Adding to list of sockets as %d\n", i);

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
					//printf("Host disconnected , ip %s , port %d \n",inet_ntoa(SvrAddr.sin_addr), ntohs(SvrAddr.sin_port));
					serverLog.push_back(string("Host disconnected , ip:")+ inet_ntoa(SvrAddr.sin_addr) + string(",port: ")+ to_string(ntohs(SvrAddr.sin_port)) + "\n");
					//cout << serverLog[serverLog.size() - 1];
					userSocketMap.erase(socketUserMap.find(sd)->second);
					socketUserMap.erase(sd);
					//Close the socket and mark as 0 in list for reuse 
					closesocket(sd);
					ClientSocket[i] = 0;
				}

			}
		}
	}
	




	//closesocket(ConnectionSocket);	//closes incoming socket
	delete DBconnection;
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();					//frees Winsock resources

	getchar();

	return 1;
}
