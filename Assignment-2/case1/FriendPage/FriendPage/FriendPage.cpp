/*
filename: FriendPage.cpp
details: Program is  an application called ‘Friendpage’, which performs certain datastoring and retrival process in the application using sqlite database.
author: J.P.Prakash
date: 07/05/2020
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
using namespace std;

int createDB(const char* stringText);
int createUserTable(const char* stringText);
int insertUserData(const char* stringText);
int updateUserData(const char* stringText);
int deleteUserData(const char* stringText);
int selectUserData(const char* stringText);

int callback(void* NotUsed, int argc, char** argv, char** azColName);

int createFriendTable(const char * stringText);
int addFriend(const char* stringText);
int showFriend(const char* stringText);
int suggestFriend(const char* stringText);

string quotesql(const string& stringText) {
	return string("'") + stringText + string("'");
}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		if (strcmp(argv[1], "-h") == 0)     //created a help command
		{
			cout << "\n Usage of file --> \n"
				"\t -give the path to save file FriendPage.db" << endl <<
				"\t -select the option from the menu" << endl <<
				"\t -Program will a database name as FriendPage.db and stores your data " << endl;
		}
	}
	else
	{
		int iChoice;
		//create a dirFile to store the database file & give path
		const char* dirFile = "E:\\C++\\Assignment-2\\case1\\friendpage.db";
		sqlite3* DataBase = NULL;

		createDB(dirFile);
		createUserTable(dirFile);
		createFriendTable(dirFile);
		do {
			cout << "\n Enter your Choice : "<< endl <<
				"\t 1. Add User" << endl <<
				"\t 2. Edit User" << endl <<
				"\t 3. Show Users" << endl <<
				"\t 4. Delete User" << endl <<
				"\t 5. Add Friend" << endl <<
				"\t 6. Show Friend" << endl <<
				"\t 7. Suggest Friend" << endl <<
				"\t 0. Exit" << endl;

			cout << "\n Enter your choice : ";
			cin >> iChoice;
			switch (iChoice)
			{
			case 1: insertUserData(dirFile);
				break;
			case 2: updateUserData(dirFile);
				break;
			case 3: selectUserData(dirFile);
				break;
			case 4: deleteUserData(dirFile);
				break;
			case 5: addFriend(dirFile);
				break;
			case 6: showFriend(dirFile);
				break;
			case 7: suggestFriend(dirFile);
				break;
			case 0: return 0;

			default: cout << "\n Invalid option \n";
				break;
			}
		} while (1);
	}
	return 0;
}

//creates the FriendPage Database
int createDB(const char * stringText)
{
	sqlite3* DataBase = NULL;
	int iDB = 0;

	iDB = sqlite3_open(stringText, &DataBase);
	sqlite3_close(DataBase);

	return 0;
}

//creates the 'User_Details' table in FriendPage database
int createUserTable(const char * stringText)
{
	sqlite3* DataBase = NULL;

	string sql = "CREATE TABLE IF NOT EXISTS USER_DETAILS("
		"NAME TEXT,"
		"EMAIL TEXT NOT NULL,"
		"PRIMARY KEY(NAME));";
	try {
		int iDB = 0;
		iDB = sqlite3_open(stringText, &DataBase);

		char* messageError;
		//executes the SQL command, if not executed "messageError" is throws an error.
		iDB = sqlite3_exec(DataBase, sql.c_str(), NULL, 0, &messageError);

		if (iDB != SQLITE_OK) {
			cerr << "\n Error User Table \n" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "\n User table created successfully \n" << endl;
		sqlite3_close(DataBase);
	}
	catch (const exception &e) {
		cerr << e.what();
	}
	return 0;
}

//insert the user data into 'User_Details' table
int insertUserData(const char* stringText)
{
	char cUserName[30];
	char cUserMail[30];
	sqlite3* DataBase = NULL;
	char* messageError;
	char moreRecords;

	int iDB = sqlite3_open(stringText, &DataBase);
	do {
		getchar();
		cout << "\n Enter username : ";
		cin.getline(cUserName, 30);
		cout << "\n Enter email id : ";
		cin.getline(cUserMail, 30);
		string sql("INSERT INTO USER_DETAILS VALUES(" + quotesql(cUserName) + "," + quotesql(cUserMail) + ");");

		iDB = sqlite3_exec(DataBase, sql.c_str(), NULL, 0, &messageError);
		if (iDB != SQLITE_OK) {
			cerr << "\n Error Insert / user may exist \n" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "\n Records created successfully \n" << endl;

		cout << "\n Add more records? (Y/N) : ";
		cin >> moreRecords;
	} while (moreRecords == 'y');
	sqlite3_close(DataBase);
	return 0;
}

//updates the 'email' based on user name
int updateUserData(const char * stringText)
{
	char cUserName[30];
	char cUserMail[30];
	sqlite3* DataBase = NULL;
	char* messageError;

	int iDB = sqlite3_open(stringText, &DataBase);

	getchar();
	cout << "\n Enter username : ";
	cin.getline(cUserName, 30);
	cout << "\n Enter new email id : ";
	cin.getline(cUserMail, 30);

	string sql("UPDATE USER_DETAILS SET EMAIL=" + quotesql(cUserMail) + " WHERE NAME=" + quotesql(cUserName) + ";");

	iDB = sqlite3_exec(DataBase, sql.c_str(), NULL, 0, &messageError);
	if (iDB != SQLITE_OK) {
		cerr << "\n Updation Error \n" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "\n Records updated successfully \n" << endl;

	sqlite3_close(DataBase);
	return 0;
}

//delete the user data
int deleteUserData(const char * stringText)
{
	sqlite3* DataBase = NULL;
	char cDelName[30];
	char* messageError;

	int iDB = sqlite3_open(stringText, &DataBase);
	cout << "\n Enter user name to delete : ";
	cin >> cDelName;

	string sql = "DELETE FROM USER_DETAILS WHERE NAME=" + quotesql(cDelName) + ";";

	iDB = sqlite3_exec(DataBase, sql.c_str(), callback, NULL, &messageError);
	if (iDB != SQLITE_OK) {
		cerr << "Error Delete" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "\n Records Deleted successfully \n" << endl;
	sqlite3_close(DataBase);
	return 0;
}

//Display contents of USER_DETAILS table
int selectUserData(const char * stringText)
{
	sqlite3* DataBase = NULL;
	int iDB = sqlite3_open(stringText, &DataBase);

	string sql = "SELECT * FROM USER_DETAILS;";

	/* an open DataBase, SQL to be evaluated, callback function, 1st argument to callback, error msg written here*/
	sqlite3_exec(DataBase, sql.c_str(), callback, NULL, NULL);
	sqlite3_close(DataBase);
	return 0;
}

//retrive contents of DataBase used by selectData()
/* argc: holds the number of results, azColName: holds each column returned in array, argv: holds each value in array*/
int callback(void * NotUsed, int argc, char ** argv, char ** azColName)
{
	for (int index = 0; index < argc; index++)
	{
		//column name & value
		cout << azColName[index] << " : " << argv[index] << endl;
	}
	cout << endl;
	return 0;
}

//creates the 'Friend_Details' table in FriendPage database
int createFriendTable(const char * stringText)
{
	sqlite3* DataBase = NULL;

	string sql = "CREATE TABLE IF NOT EXISTS FRIEND_DETAILS("
		"NAME TEXT REFERENCES USER_DETAILS(NAME),"
		"FRIEND TEXT UNIQUE);";
	try {
		int iDB = 0;
		iDB = sqlite3_open(stringText, &DataBase);

		char* messageError;
		iDB = sqlite3_exec(DataBase, sql.c_str(), NULL, 0, &messageError);

		if (iDB != SQLITE_OK) {
			cerr << "\n Error Friend Table \n " << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "\n Friend Table create successfully" << endl;
		sqlite3_close(DataBase);
	}
	catch (const exception &e) {
		cerr << e.what();
	}
	return 0;
}

//insert the user's friends data into 'Friend_Details' table
int addFriend(const char * stringText)
{
	char cName[30];
	char cFriend[30];
	sqlite3* DataBase = NULL;
	char* messageError;
	char moreRecords;;

	int iDB = sqlite3_open(stringText, &DataBase);

	getchar();
	cout << "\n Enter your username : ";
	cin.getline(cName, 30);
	cout << "\n Enter friend's name : ";
	cin.getline(cFriend, 30);
	string sql("INSERT INTO FRIEND_DETAILS VALUES("+quotesql(cName)+","+quotesql(cFriend)+");");
	/*
	string sql = "SELECT USER_DETAILS.NAME, USER_DETAILS.EMAIL, FRIEND_DETAILS.FRIEND "
		"FROM USER_DETAILS JOIN FRIEND_DETAILS ON (USER_DETAILS.NAME = FRIEND_DETAILS.NAME) "
		"WHERE FRIEND_DETAILS.NAME=" + quotesql(cName) + ";";
	*/
	iDB = sqlite3_exec(DataBase, sql.c_str(), NULL, 0, &messageError);
	if (iDB != SQLITE_OK) {
		cerr << "\n Error adding friend/ friend already exist. \n" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "\n Added friend successfully \n" << endl;
	sqlite3_close(DataBase);
	return 0;
}

//shows specific user's details along with there 
int showFriend(const char * stringText)
{
	try {
		sqlite3* DataBase = NULL;
		char cName[30];
		char* messageError;

		int iDB = sqlite3_open(stringText, &DataBase);

		cout << "Enter your user name : ";
		cin >> cName;
		string sql = "SELECT USER_DETAILS.NAME, USER_DETAILS.EMAIL, FRIEND_DETAILS.FRIEND "
			"FROM USER_DETAILS JOIN FRIEND_DETAILS ON (USER_DETAILS.NAME = FRIEND_DETAILS.NAME) "
			"WHERE FRIEND_DETAILS.NAME=" + quotesql(cName) + ";";

		/* an open DataBase, SQL to be evaluated, callback function, 1st argument to callback, error msg written here*/

		iDB = sqlite3_exec(DataBase, sql.c_str(), callback, NULL, &messageError);
		if (iDB != SQLITE_OK) {
			cerr << "Error showing friend/User does not exist" << endl;
			sqlite3_free(messageError);
		}
		sqlite3_close(DataBase);
	}
	catch (const exception &e) {
		cerr << e.what();
	}
	return 0;
}

int suggestFriend(const char * stringText)
{
	try {
		sqlite3* DataBase = NULL;
		char cName[30];
		char* messageError;

		int iDB = sqlite3_open(stringText, &DataBase);

		cout << "Enter your user name : ";
		cin >> cName;
		string sql = "SELECT FRIEND_DETAILS.FRIEND "
			"FROM FRIEND_DETAILS JOIN USER_DETAILS ON (FRIEND_DETAILS.NAME = USER_DETAILS.NAME) "
			"WHERE FRIEND_DETAILS.NAME NOT LIKE " + quotesql(cName) + ";";

		/* an open DataBase, SQL to be evaluated, callback function, 1st argument to callback, error msg written here*/

		iDB = sqlite3_exec(DataBase, sql.c_str(), callback, NULL, &messageError);
		if (iDB != SQLITE_OK) {
			cerr << "Error suggesting friend" << endl;
			sqlite3_free(messageError);
		}
		sqlite3_close(DataBase);
	}
	catch (const exception &e) {
		cerr << e.what();
	}
	return 0;
}






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
