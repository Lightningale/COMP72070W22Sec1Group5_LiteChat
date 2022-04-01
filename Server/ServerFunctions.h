#pragma once
#include <windows.networking.sockets.h>
#include "../Client/Packets.h"
#include "database.h"
#include <vector>
#include <iterator>
#include <map>
#include <ctime>
map<SOCKET,string> socketUserMap;
map<string, SOCKET> userSocketMap;
string trim(const std::string& str, const std::string& whitespace = " \t\f\n\r\v")
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}
void sendFailResponse(SOCKET socket, const char* failmsg)
{
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(failmsg, 0);
	//pkt->GetSerializedData(TxBuffer + typeNameSize);
	pkt->GetSerializedData(TxBuffer);
	//send string over socket
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
}
void sendLogin(SOCKET socket, AccountPacket account)
{
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(respLoginSuccess, 1);

	//memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	//pkt->GetSerializedData(TxBuffer + typeNameSize);
	pkt->GetSerializedData(TxBuffer);
	account.GetSerializedData(TxBuffer + sizeof(HeaderPacket));
	//send string over socket
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
}
void sendLogout(SOCKET socket, AccountPacket account)
{
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(respLogoutSuccess, 1);

	//memcpy(TxBuffer, pkt->GetType(), typeNameSize);
	//pkt->GetSerializedData(TxBuffer + typeNameSize);
	pkt->GetSerializedData(TxBuffer);
	account.GetSerializedData(TxBuffer + sizeof(HeaderPacket));
	//send string over socket
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
}
//send the member and message data of a chatroom
void sendChatroomInfo(SOCKET socket, long chatroomID)
{
	//member data in database. replace this with data retrieved from database
	vector<AccountData> memberList;
	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	result = statement->executeQuery("SELECT Users.* FROM RoomMembers INNER JOIN Users ON RoomMembers.username=Users.username WHERE RoomMembers.roomID = '" + to_string(chatroomID) + "'");
	while (result->next())
	{
		AccountData temp;
		strncpy_s(temp.username, result->getString("username").c_str(), usernameLength);
		//strncpy(temp.password)
		memberList.push_back(temp);
	}
	delete result;
	/////////////////////////////////////////////////////
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(respMemberList, memberList.size());
	pkt->GetSerializedData(TxBuffer);
	memcpy(TxBuffer + sizeof(HeaderPacket), &chatroomID, sizeof(long));
	for (int i = 0; i < memberList.size(); i++)
	{
		memcpy(TxBuffer + sizeof(HeaderPacket) + sizeof(long) + sizeof(AccountData) * i, &memberList[i], sizeof(AccountData));
	}
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;

	//message data in database. replace this with data retrieved from database
	vector<MessageData>messageList;
	result = statement->executeQuery("SELECT * FROM Messages WHERE roomID = '" + to_string(chatroomID) + "'");
	while (result->next())
	{
		MessageData temp;
		strncpy_s(temp.username, result->getString("username").c_str(), usernameLength);
		strncpy_s(temp.message, result->getString("message").c_str(), messageLength);
		temp.chatroomID = result->getInt("roomID");
		temp.hasImage = result->getBoolean("hasImage");
		temp.timestamp = static_cast<time_t>(result->getInt("timestamp"));
		//strncpy(temp.password)
		messageList.push_back(temp);
	}

	/////////////////////////////////////////////////////
	pkt = new HeaderPacket(respMessageList, messageList.size());
	pkt->GetSerializedData(TxBuffer);
	for (int i = 0; i < messageList.size(); i++)
	{
		memcpy(TxBuffer + sizeof(HeaderPacket) + sizeof(MessageData) * i, &messageList[i], sizeof(MessageData));
	}
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
}

//send a list of all chatrooms the user is in
void sendChatroomList(SOCKET socket, const char* username)
{
	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	vector<ChatroomData> chatroomList;
	result = statement->executeQuery("SELECT ChatRooms.* FROM RoomMembers INNER JOIN ChatRooms ON RoomMembers.roomID = ChatRooms.roomID WHERE RoomMembers.username = '" + string(username, usernameLength) + "';");
	while (result->next())
	{
		ChatroomData temp;
		strncpy_s(temp.chatroomName, result->getString("name").c_str(), chatroomNameSize);
		strncpy_s(temp.owner, result->getString("name").c_str(), usernameLength);
		temp.chatroomID = result->getInt("roomID");
		chatroomList.push_back(temp);
	}
	delete result;
	delete statement;
	//replace this with data retrieved from database

	/////////////////////////////////////////////////////
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(respChatroomList, chatroomList.size());
	pkt->GetSerializedData(TxBuffer);
	for (int i = 0; i < chatroomList.size(); i++)
	{
		memcpy(TxBuffer + sizeof(HeaderPacket) + sizeof(ChatroomData) * i, &chatroomList[i], sizeof(ChatroomData));
	}
	send(socket, TxBuffer, sizeof(TxBuffer), 0);
	delete pkt;
	//send the member and message data of each chatroom
	for (int i = 0; i < chatroomList.size(); i++)
	{
		sendChatroomInfo(socket, chatroomList[i].chatroomID);
	}
}
//send a newly joined member to all active users
void RelayMember(SOCKET thisSocket,AccountData actData, long chatroomID)
{

	cout << "Relay Member activated" << endl;
	cout << "user socket map:";
	for (auto it = userSocketMap.cbegin(); it != userSocketMap.cend(); ++it)
	{
		cout << it->first << "," << it->second <<";";
	}
	cout <<endl<< "socket user map:";
	for (auto it = socketUserMap.cbegin(); it != socketUserMap.cend(); ++it)
	{
		cout << it->second << "," << it->first << ";";
	}
	cout << endl;
	char TxBuffer[1024] = {};
	Packet* pkt = new HeaderPacket(respMemberList, 1);
	pkt->GetSerializedData(TxBuffer);
	memcpy(TxBuffer + sizeof(HeaderPacket), &chatroomID, sizeof(long));
	memcpy(TxBuffer + sizeof(HeaderPacket) + sizeof(long), &actData, sizeof(AccountData));
	//member data in database. replace this with data retrieved from database
	vector<AccountData> memberList;
	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	result = statement->executeQuery("SELECT Users.* FROM RoomMembers INNER JOIN Users ON RoomMembers.username = Users.username WHERE RoomMembers.roomID = '" + to_string(chatroomID) + "'");
	while (result->next())
	{
		string tempusername = string(result->getString("username"));
		//char usernameBuff[usernameLength] = { 0 };
		//strncpy_s(usernameBuff, tempusername.c_str(), tempusername.size());
		//tempusername = string(usernameBuff);
		cout << "found user " << tempusername<<endl;
		if (userSocketMap.count(tempusername)) 
		{
			if (userSocketMap.find(tempusername)->second != thisSocket)
			{
				send(userSocketMap.find(tempusername)->second, TxBuffer, sizeof(TxBuffer), 0);
				cout << "RelayMember sent " + string(actData.username, usernameLength) + " in chatroom #" + to_string(chatroomID) + " to " + tempusername + " ON " + to_string(userSocketMap.find(tempusername)->second)+" FROM + "<<thisSocket << endl;
			}
		}
	}

	delete pkt;
	delete result;
	delete statement;
}

//create a new chatroom in database and store data in dest.
void CreateChatroom(SOCKET socket, const char* chatroomName, const char* username)
{

	//create a room entry in database and store data here

	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	string sqlbuff = "'" + string(chatroomName,chatroomNameSize) + "', " + "'" + string(username, usernameLength) + "'" + ");";
	sql::SQLString query = sqlbuff;
	//statement->execute("INSERT INTO Chatrooms(name, owner) VALUES (" + query);
	string debug = string(chatroomName, chatroomNameSize);
	cout << "Create chatroom:'" << debug <<"', owner:'"<< string(username, usernameLength)<<"'"<< endl;
	statement->execute("INSERT INTO Chatrooms SET name='" + debug + "',owner=(SELECT username FROM Users WHERE username='" + string(username, usernameLength) + "');");
	//
	result = statement->executeQuery("SELECT * FROM Chatrooms Where owner= '" + string(username, usernameLength) + "' ORDER BY roomID DESC;");
	if (result->next())
	{
		ChatroomData roomData;
		memcpy(roomData.chatroomName, result->getString("name").c_str(), chatroomNameSize);
		memcpy(roomData.owner, result->getString("owner").c_str(), usernameLength);
		roomData.chatroomID = result->getInt("roomID");
		//statement->execute("INSERT INTO RoomMembers(roomID,username) Values(" + to_string(roomData.chatroomID) + "," + string(username, usernameLength) + "');");
		statement->execute("INSERT INTO RoomMembers SET roomID=(SELECT roomID from Chatrooms WHERE roomID="+to_string(roomData.chatroomID)+"),username=(SELECT username FROM Users WHERE username='"+roomData.owner+"');");
		char TxBuffer[1024] = {};
		Packet* pkt = new HeaderPacket(respChatroomList, 1);
		pkt->GetSerializedData(TxBuffer);
		memcpy(TxBuffer + sizeof(HeaderPacket), &roomData, sizeof(ChatroomData));
		send(socket, TxBuffer, sizeof(TxBuffer), 0);
		sendChatroomInfo(socket, roomData.chatroomID);
	}
	delete statement;
	delete result;
	//ChatroomData mockRoom = { "testCreateRoom","someUser",10000 + rand() };
	
}
//return false if no matching chatroom found, otherwise store chatroom data in dest
void JoinChatroom(SOCKET socket, long chatroomID)
{
	statement = connection->createStatement();
	statement->execute("USE " + database_name);

	//check if room id exists
	result = statement->executeQuery("SELECT * FROM Chatrooms WHERE roomID = " + to_string(chatroomID) + ";");
	if (result->next())
	{
		ChatroomData roomData;
		strncpy_s(roomData.chatroomName, result->getString("name").c_str(), chatroomNameSize);
		strncpy_s(roomData.owner, result->getString("owner").c_str(), usernameLength);
		roomData.chatroomID = result->getInt("roomID");
		//check if user already exists in room
		result= statement->executeQuery("SELECT * FROM RoomMembers WHERE roomID = " + to_string(chatroomID) + " AND username='" + socketUserMap.find(socket)->second+"';");
		if (result->rowsCount() == 0)
		{
			statement->execute("INSERT INTO RoomMembers SET roomID=(SELECT roomID from Chatrooms WHERE roomID=" + to_string(chatroomID) + "),username=(SELECT username FROM Users WHERE username='" + socketUserMap.find(socket)->second + "');");
			delete statement;
			delete result;

			/// <summary>
			char TxBuffer[1024] = {};
			Packet* pkt = new HeaderPacket(respChatroomList, 1);
			pkt->GetSerializedData(TxBuffer);
			memcpy(TxBuffer + sizeof(HeaderPacket), &roomData, sizeof(ChatroomData));
			
			send(socket, TxBuffer, sizeof(TxBuffer), 0);
			delete pkt;
			//send the member and message data of  chatroom
			sendChatroomInfo(socket, roomData.chatroomID);
			
			/// </summary>
			/// <param name="socket"></param>
			/// <param name="chatroomID"></param>

			//sendChatroomInfo(socket, chatroomID);
			AccountData newMember={0};
			strncpy_s(newMember.username, socketUserMap.find(socket)->second.c_str(), usernameLength);
			RelayMember(socket,newMember, chatroomID);

		}
	}
	else
	{
		delete statement;
		delete result;
		sendFailResponse(socket, respJoinRoomFail);
	}
	
}
//store a message into the chatroom message table in database
void StoreMessage(MessagePacket msgPkt)
{
	MessageData msgBuf = msgPkt.GetMessageData();
	statement = connection->createStatement();
	//sql::SQLString query = "INSERT INTO Messages SET roomID=(SELECT roomID from Chatrooms WHERE roomID=" + to_string(msgBuf.chatroomID) + "),username=(SELECT username FROM Users WHERE username='" + string(msgBuf.username, usernameLength) + "'),timestamp=FROM_UNIXTIME(" + to_string(msgBuf.timestamp) + "),message='" + string(msgBuf.message, messageLength) + "';";
	sql::SQLString query = "INSERT INTO Messages SET hasImage="+to_string(msgBuf.hasImage)+",roomID=" + to_string(msgBuf.chatroomID) + ",username='" + string(msgBuf.username, usernameLength) + "',timestamp=FROM_UNIXTIME(" + to_string(msgBuf.timestamp) + "),message='" + string(msgBuf.message) + "';";
	cout << query << endl;
	statement->execute(query);
	//statement->execute("INSERT INTO Messages(roomID, username, timestamp, message) VALUES (" + to_string(msgBuf.chatroomID)+",'"+msgBuf.username+"',FROM_UNIXTIME("+to_string(msgBuf.timestamp)+"),'"+msgBuf.message+"');");
}
//send a message to every connected socket where the logged in user is in the chatroom
void RelayMessage(SOCKET socket, MessagePacket msgPkt)
{
	char TxBuffer[1024] = {};
	Packet* header = new HeaderPacket(respMessageList, 1);
	header->GetSerializedData(TxBuffer);
	MessageData msgBuf = msgPkt.GetMessageData();
	memcpy(TxBuffer + sizeof(HeaderPacket), &msgBuf, sizeof(MessageData));
	//msgPkt.GetSerializedData(TxBuffer+sizeof(HeaderPacket));
	msgPkt.Print();
	
	
	//send(socket, TxBuffer, sizeof(TxBuffer), 0);


	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	//result = statement->executeQuery("SELECT Users.* FROM RoomMembers INNER JOIN Users ON RoomMembers.username = Users.username WHERE RoomMembers.roomID = '" + to_string(msgBuf.chatroomID) + "'");
	result = statement->executeQuery("SELECT * FROM RoomMembers WHERE roomID = '" + to_string(msgBuf.chatroomID) + "'");
	while (result->next())
	{
		string tempusername = string(result->getString("username"));
		//char usernameBuff[usernameLength] = { 0 };
		//strncpy_s(usernameBuff, tempusername.c_str(), tempusername.size());
		//tempusername = string(usernameBuff);
		//cout << "found user " << tempusername << endl;
		if (userSocketMap.count(tempusername))
		{

				send(userSocketMap.find(tempusername)->second, TxBuffer, sizeof(TxBuffer), 0);
				//cout << "RelayMessage sent " + string(actData.username, usernameLength) + " in chatroom #" + to_string(chatroomID) + " to " + tempusername + " ON " + to_string(userSocketMap.find(tempusername)->second) + " FROM + " << thisSocket << endl;
		}
	}

	delete header;
	delete result;
	delete statement;
}


bool VerifyRegister(SOCKET socket,const char* username, const char* password)
{
	//verify if account exists
	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	result = statement->executeQuery("SELECT username FROM Users WHERE username = '"+string(username,usernameLength)+"'");
	if (result->rowsCount() >0)
	{
		cout << "username "<<username<<" already exists" << endl;
		delete statement;
		delete result;
		return false;
	}
	delete result;
	//register account
	string concacenate_to_sql = "'" + string(username,usernameLength) + "', " + "'" + password + "'" + ");";
	sql::SQLString query = concacenate_to_sql;

	statement->execute("USE " + database_name);
	statement->execute("INSERT INTO Users(username, password) VALUES (" + query);
	result = statement->executeQuery("SELECT * FROM Users WHERE username = '" + string(username, usernameLength) + "' AND password = '" + string(password, passwordLength) + "';");
	while (result->next())
	{

		//add user to user socket list
		string tempname = result->getString("username");
		socketUserMap.insert(pair<SOCKET, string>(socket, tempname));
		userSocketMap.insert(pair<string, SOCKET>(tempname, socket));
		delete statement;
		delete result;
		return true;
	}
}
bool VerifyLogin( SOCKET socket,const char* username, const char* password)
{
	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	result = statement->executeQuery("SELECT * FROM Users WHERE username = '" + string(username, usernameLength) + "' AND password = '"+ string(password, passwordLength)+"';");
	while(result->next())
	{
		
		//add user to user socket list
		string tempname = result->getString("username");
		socketUserMap.insert(pair<SOCKET, string>(socket, tempname));
		userSocketMap.insert(pair<string, SOCKET>(tempname, socket));
		delete statement;
		delete result;
		return true;
	}
	delete statement;
	delete result;
	return false;
}

bool RecvClientPacket(SOCKET ConnectionSocket)
{
	char RxBuffer[1024] = {};
	char RxPacketType[typeNameSize] = {};
	if (recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0) <= 0)
		return false;
	//cout << RxBuffer << endl;
	memcpy(RxPacketType, RxBuffer, typeNameSize);

	//handle register and login requests
	if (memcmp(RxPacketType, typeAccount, typeNameSize) == 0)
	{
		//rxPkt = new AccountPacket(RxBuffer + typeNameSize);
		//rxPkt->Print();
		char Buffer[sizeof(AccountPacket)] = {};
		memcpy(Buffer, RxBuffer, sizeof(AccountPacket));
		AccountPacket rxPkt(Buffer);
		rxPkt.Print();
		//register
		if (strncmp(rxPkt.GetAction(), actionRegister, typeNameSize) == 0)
		{
			if (VerifyRegister(ConnectionSocket, rxPkt.GetUsername(), rxPkt.GetPassword()))
			{
				sendLogin(ConnectionSocket, rxPkt);
				sendChatroomList(ConnectionSocket, rxPkt.GetUsername());
			}
			else
			{
				sendFailResponse(ConnectionSocket, respRegisterFail);
			}
		}
		//login
		else if (strncmp(rxPkt.GetAction(), actionLogin, typeNameSize) == 0)
		{
			if (VerifyLogin(ConnectionSocket, rxPkt.GetUsername(), rxPkt.GetPassword()))
			{
				sendLogin(ConnectionSocket, rxPkt);
				sendChatroomList(ConnectionSocket, rxPkt.GetUsername());
			}
			else
			{
				sendFailResponse(ConnectionSocket, respLoginFail);
			}
		}
		//logout
		else if (strncmp(rxPkt.GetAction(), actionLogout, typeNameSize) == 0)
		{
			userSocketMap.erase(socketUserMap.find(ConnectionSocket)->second);
			socketUserMap.erase(ConnectionSocket);

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
			CreateChatroom(ConnectionSocket, rxRoomPkt.GetChatroomName(), rxRoomPkt.GetOwnerName());
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
	return true;

}