#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

// username and password are subjected to change after integration
//Change to port number and account passwords on your local machine
const string server = "tcp://127.0.0.1:3308";
const sql::SQLString username = "connector";
const sql::SQLString password = "connectorPassword";
const sql::SQLString database_name = "LiteChat";

sql::mysql::MySQL_Driver* driver;
sql::Connection* connection;
sql::Statement* statement;
sql::ResultSet* result;


//sql::Connection* DB_CONNECT();
//Sets up the connection between the C++ connector to the MySQL server
sql::Connection* DB_CONNECT() {

	driver = sql::mysql::get_mysql_driver_instance();

	return connection = driver->connect(server, username, password);
}
/*
void DB_INSERT_INTO_USERS(sql::Connection*, std::string, std::string, int);
void DB_INSERT_INTO_CHATROOMS(sql::Connection*, std::string, std::string, int);

void DB_CREATE_USER_TABLE(sql::Connection*);
void DB_CREATE_CHATROOM_TABLE(sql::Connection*);
void DB_CREATE_MESSAGE_TABLE(sql::Connection*);
void DB_CREATE_USER_ROOM_TABLE(sql::Connection*, std::string);
void DB_CREATE_CHATROOM_USERS_TABLE(sql::Connection*, std::string);

bool DB_CHECK_USER(sql::Connection*, std::string);
void DB_REMOVE_USER(sql::Connection*, std::string);
void DB_REMOVE_CHATROOM(sql::Connection*, std::string);
*/