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

sql::Connection* DB_CONNECT();

void DB_INSERT_INTO_USERS(sql::Connection*, std::string,std::string, int);
void DB_INSERT_INTO_CHATROOMS(sql::Connection*, std::string, std::string, int);

void DB_CREATE_USER_TABLE(sql::Connection*);
void DB_CREATE_CHATROOM_TABLE(sql::Connection*);
void DB_CREATE_MESSAGE_TABLE(sql::Connection*);
void DB_CREATE_USER_ROOM_TABLE(sql::Connection*,std::string);
void DB_CREATE_CHATROOM_USERS_TABLE(sql::Connection*, std::string);

bool DB_CHECK_USER(sql::Connection*, std::string);
void DB_REMOVE_USER(sql::Connection*, std::string);
void DB_REMOVE_CHATROOM(sql::Connection*, std::string);