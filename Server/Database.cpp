#include "Database.h"
using namespace std;
using namespace sql;

sql::mysql::MySQL_Driver* driver;
sql::Connection* connection;
sql::Statement* statement;
sql::ResultSet* result;

// username and password are subjected to change after integration
const string server = "tcp://127.0.0.1:3306";
const sql::SQLString username = "root";
const sql::SQLString password = "Cc8654240";
const sql::SQLString database_name = "litechat";

//Sets up the connection between the C++ connector to the MySQL server
sql::Connection* DB_CONNECT() {
	
	driver = sql::mysql::get_mysql_driver_instance();

	return connection = driver->connect(server, username, password);
}

// Creates the user tables that contains all the user information 
void DB_CREATE_USER_TABLE(sql::Connection* connection) {

	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	statement->execute("DROP TABLE IF EXISTS users");
	statement->execute("CREATE TABLE users(username CHAR(20) UNIQUE, password CHAR(20), id INT UNIQUE PRIMARY KEY)");
	delete statement;
}

// Creates the chatroom tables that contains all chatrooms
void DB_CREATE_CHATROOM_TABLE(sql::Connection* connection) {

	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	statement->execute("DROP TABLE IF EXISTS chatrooms");
	statement->execute("CREATE TABLE chatrooms(name CHAR(20), creator CHAR(20), id INT UNIQUE PRIMARY KEY)");
	delete statement;
}

// Creates a message table for chatroom to store its messages
void DB_CREATE_MESSAGE_TABLE(sql::Connection* connection) {

	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	statement->execute("DROP TABLE IF EXISTS messages");
	statement->execute("CREATE TABLE messages(id INT UNIQUE, username CHAR(20), timestamp TIMESTAMP, message CHAR(200), imageaddress CHAR(20))");
	delete statement;
}

// Creates a table for a user to store all the user's room IDs
void DB_CREATE_USER_ROOM_TABLE(sql::Connection* connection, string user) {
	
	sql::SQLString query = user;
	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	statement->execute("DROP TABLE IF EXISTS " + query);
	statement->execute("CREATE TABLE " + query + "(roomID INT, FOREIGN KEY (id) REFERENCES chatrooms(id) ON UPDATE CASCADE ON DELETE CASCADE)");
	delete statement;
}

// Creates a table for a chatroom to store all its users' IDs
void DB_CREATE_CHATROOM_USERS_TABLE(sql::Connection* connection, string chatroom_name) {

	sql::SQLString query = chatroom_name;
	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	statement->execute("DROP TABLE IF EXISTS " + query);
	statement->execute("CREATE TABLE " + query + "(userID INT, FOREIGN KEY (id) REFERENCES users(id) ON UPDATE CASCADE ON DELETE CASCADE)");
	delete statement;
}

// Insert command to add a user to the user table 
void DB_INSERT_INTO_USERS(sql::Connection*, string username, string password, int id) {
	

	string concacenate_to_sql = "'" + username + "', " + "'" + password + "', " + to_string(id) + ")";
	sql::SQLString query = concacenate_to_sql;

	statement = connection->createStatement();		
	statement->execute("USE " + database_name);
	statement->execute("INSERT INTO users(username, password, id) VALUES (" + query);
	delete statement;
}

// Insert command to add a chatroom to the chatroom table 
void DB_INSERT_INTO_CHATROOMS(sql::Connection*, string name, string creator, int id) {

	string concacenate_to_sql = "'" + name + "', " + "'" + creator + "', " + to_string(id) + ")";
	sql::SQLString query = concacenate_to_sql;

	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	statement->execute("INSERT INTO chatrooms(name, creator, id) VALUES (" + query);
	delete statement;
}

// Checks to see if the username exists in the user table
bool DB_CHECK_USER(sql::Connection*, string user) {

	statement = connection->createStatement();
	statement->execute("USE " + database_name);
	result = statement->executeQuery("SELECT username FROM users");
	while (result->next()) {
		if (user == result->getString("username")) {
			cout << "username already exists" << endl;
			return true;
		}
	}
	delete statement;
	delete result;
	return false;
}

// Removes a user from the user table 
void DB_REMOVE_USER(sql::Connection*, string user) {

	string concacenate_to_sql = "'" + user + "'";
	sql::SQLString query = concacenate_to_sql;
	statement = connection->createStatement();
	statement->execute("DELETE from users where username = " + query);

	delete statement;
}

// Removes a chatroom from the user table 
void DB_REMOVE_CHATROOM(sql::Connection*, string chatroom_name) {

	string concacenate_to_sql = "'" + chatroom_name + "'";
	sql::SQLString query = concacenate_to_sql;
	statement = connection->createStatement();
	statement->execute("DELETE from chatrooms where name = " + query);

	delete statement;
}