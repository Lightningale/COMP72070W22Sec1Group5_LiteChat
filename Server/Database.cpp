#include "Database.h"
using namespace std;

const string server = "";
const string username = "";
const string password = "";

int main(void) {

	sql::Driver* driver;
	sql::Connection* connection;
	sql::Statement* statement;
	sql::PreparedStatement* preparedstatement;

	try {
		driver = get_driver_instance();
		connection = driver->connect(server, username, password);
	} catch (sql::SQLException &e){
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	return 0;
}