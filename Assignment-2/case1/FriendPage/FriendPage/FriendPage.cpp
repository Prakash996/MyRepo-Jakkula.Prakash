/*
filename: FriendPage.cpp
details: Program is  an application called ‘Friendpage’, which performs certain datastoring and retrival process in the application using sqlite database.
author: J.P.Prakash
date: 07/05/2020
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
using namespace std;

static int createDB(const char* s);
static int createUserTable(const char* s);
static int insertUserData(const char* s);
static int updateUserData(const char* s);
static int deleteUserData(const char* s);
static int selectUserData(const char* s);

static int callback(void* NotUsed, int argc, char** argv, char** azColName);

static int createFriendTable(const char * s);
static int addFriend(const char* s);
static int showFriend(const char* s);

string quotesql(const string& s) {
	return string("'") + s + string("'");
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
		char iContinue;
		//create a dirFile to store the database file & give path
		const char* dirFile = "E:\\C++\\Assignment-2\\case1\\friendpage.db";
		sqlite3* DataBase;

		createDB(dirFile);
		createUserTable(dirFile);
		createFriendTable(dirFile);

		do {
			cout << "\n\t 1. Add User" << endl <<
				"\t 2. Edit User" << endl <<
				"\t 3. Show Users" << endl <<
				"\t 4. Delete User" << endl <<
				"\t 5. Add Friend" << endl <<
				"\t 6. Show Friend" << endl;

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
			default: cout << "\n Invalid option \n";
				break;
			}
			cout << "\n do you want to continue (Y/N) : ";
			cin >> iContinue;
		} while (iContinue == 'y');
	}
	return 0;
}

//creates the FriendPage Database
static int createDB(const char * s)
{
	sqlite3* DataBase;
	int iDB = 0;

	iDB = sqlite3_open(s, &DataBase);
	sqlite3_close(DataBase);

	return 0;
}

//creates the 'User_Details' table in FriendPage database
static int createUserTable(const char * s)
{
	sqlite3* DataBase;

	string sql = "CREATE TABLE IF NOT EXISTS USER_DETAILS("
		"NAME TEXT,"
		"EMAIL TEXT NOT NULL,"
		" PRIMARY KEY(NAME));";
	try {
		int iDB = 0;
		iDB = sqlite3_open(s, &DataBase);

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
static int insertUserData(const char* s)
{
	char cUserName[30];
	char cUserMail[30];
	sqlite3* DataBase;
	char* messageError;
	char moreRecords;;

	int iDB = sqlite3_open(s, &DataBase);
	do {
		getchar();
		cout << "\n Enter username : ";
		cin.getline(cUserName, 30);
		cout << "\n Enter email id : ";
		cin.getline(cUserMail, 30);
		string sql("INSERT INTO USER_DETAILS VALUES(" + quotesql(cUserName) + "," + quotesql(cUserMail) + ");");

		iDB = sqlite3_exec(DataBase, sql.c_str(), NULL, 0, &messageError);
		if (iDB != SQLITE_OK) {
			cerr << "\n Error Insert \n" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "\n Records created successfully \n" << endl;

		cout << "\n Add more records? (Y/N) : ";
		cin >> moreRecords;
	} while (moreRecords == 'y');
	return 0;
}

//updates the 'email' based on user name
static int updateUserData(const char * s)
{
	char cUserName[30];
	char cUserMail[30];
	sqlite3* DataBase;
	char* messageError;

	int iDB = sqlite3_open(s, &DataBase);

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
	return 0;
}

//delete the user data
static int deleteUserData(const char * s)
{
	sqlite3* DataBase;
	char cDelName[30];
	char* messageError;

	int iDB = sqlite3_open(s, &DataBase);
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

	return 0;
}

//Display contents of USER_DETAILS table
static int selectUserData(const char * s)
{
	sqlite3* DataBase;
	int iDB = sqlite3_open(s, &DataBase);

	string sql = "SELECT * FROM USER_DETAILS;";

	/* an open DataBase, SQL to be evaluated, callback function, 1st argument to callback, error msg written here*/
	sqlite3_exec(DataBase, sql.c_str(), callback, NULL, NULL);

	return 0;
}

//retrive contents of DataBase used by selectData()
/* argc: holds the number of results, azColName: holds each column returned in array, argv: holds each value in array*/
static int callback(void * NotUsed, int argc, char ** argv, char ** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		//column name & value
		cout << azColName[i] << " : " << argv[i] << endl;
	}
	cout << endl;
	return 0;
}

//creates the 'Friend_Details' table in FriendPage database
static int createFriendTable(const char * s)
{
	sqlite3* DataBase;

	string sql = "CREATE TABLE IF NOT EXISTS FRIEND_DETAILS("
		"NAME TEXT REFERENCES USER_DETAILS(NAME),"
		"FRIEND TEXT NULL UNIQUE);";
	try {
		int iDB = 0;
		iDB = sqlite3_open(s, &DataBase);

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
int addFriend(const char * s)
{
	char cName[30];
	char cFriend[30];
	sqlite3* DataBase;
	char* messageError;
	char moreRecords;;

	int iDB = sqlite3_open(s, &DataBase);

	getchar();
	cout << "\n Enter your username : ";
	cin.getline(cName, 30);
	cout << "\n Enter friend's name : ";
	cin.getline(cFriend, 30);
	string sql("INSERT INTO FRIEND_DETAILS VALUES(" + quotesql(cName) + "," + quotesql(cFriend) + ");");

	iDB = sqlite3_exec(DataBase, sql.c_str(), NULL, 0, &messageError);
	if (iDB != SQLITE_OK) {
		cerr << "\n Error adding friend \n" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "\n Added friend successfully \n" << endl;
	return 0;
}

//shows specific user's details along with there 
int showFriend(const char * s)
{
	try {
		sqlite3* DataBase;
		char cName[30];
		char* messageError;

		int iDB = sqlite3_open(s, &DataBase);

		cout << "Enter your user name : ";
		cin >> cName;
		string sql = "SELECT USER_DETAILS.NAME, USER_DETAILS.EMAIL, FRIEND_DETAILS.FRIEND "
			"FROM USER_DETAILS LEFT JOIN FRIEND_DETAILS ON (USER_DETAILS.NAME = FRIEND_DETAILS.NAME) "
			"WHERE FRIEND_DETAILS.NAME = " + quotesql(cName) + ";";

		/* an open DataBase, SQL to be evaluated, callback function, 1st argument to callback, error msg written here*/

		iDB = sqlite3_exec(DataBase, sql.c_str(), callback, NULL, &messageError);
		if (iDB != SQLITE_OK) {
			cerr << "Error showing friend" << endl;
			sqlite3_free(messageError);
		}
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