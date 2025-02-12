/*
    title: driver.cpp
    author: Jonah Perkins
    date: 4/3/23
    purpose: keeps login credentials and allows the user to login, create
	an account, and remove a user.
*/

#include <iostream>
#include <fstream>
#include "sha256.h"
#include "hashTable.h"

using namespace std;

int main()
{
	ifstream file("testlist.txt");
	int menuChoice;
	int numUsers;
	string user, pwd, salt;
	string username, password;
	hashTable* table; // creates the hashtable pointer
	
	// gets the given users from the txt file
	if(file.is_open()) {
	file >> numUsers;
	file.ignore(1, '\n');
	table = new hashTable(numUsers); // dynamically allocates a hashTable

	while(getline(file, user))
	{
		getline(file, pwd);
		salt = table -> generateSalt(); // generates salt
		pwd += salt; // appends salt
		pwd = sha256(pwd); // hashes the password
		table -> addEntry(user, salt, pwd); // adds the new entry
	}} 
	
	// implements the menu
	do
	{
		cout << "\nWhat would you like to do?\n";
		cout << "1.  Login.\n";
		cout << "2.  Create account.\n";
		cout << "3.  Delete account.\n";
		cout << "4.  Exit.\n";
		cout << "CHOOSE 1-4:  ";
		cin >> menuChoice;
		while(menuChoice < 1 || menuChoice > 4)
		{
			cout << "That is not a valid choice.\n";
			cout << "CHOOSE 1-4:  ";
			cin >> menuChoice;
		}
		
		switch(menuChoice)
		{
			case 1:	cout << "enter your username:  ";
					cin >> username;
					cout << "enter your password:  ";
					cin >> password;
					salt = table -> getSalt(username); // gets the salt for that username
					password += salt; // appends the salt
					password = sha256(password); // hashes the password to check it
					if(table -> validateLogin(username, password)) // validates the login
						cout << "login successful\n";
					else
						cout << "invalid credentials\n";
					break;
					
			case 2: cout << "enter your new username:  ";
					cin >> username;
					cout << "enter your new password:  ";
					cin >> password;
					salt = table -> generateSalt(); // generates a new salt
					password += salt; // appends the salt
					password = sha256(password); // hashes the new password to add it
					table -> addEntry(username, salt, password); // attempts the add the new entry
					break;
					
			case 3:	cout << "enter your username:  ";
					cin >> username;
					cout << "enter your password:  ";
					cin >> password;
					salt = table -> getSalt(username); // gets the salt for that username
					password += salt; // appends the salt
					password = sha256(password); // hashes the password to check it
					if(table -> removeUser(username, password)) // attempts to remove the user
						cout << "user removed successfully.\n";
					else
						cout << "invalid credentials, cannot remove user.\n";
					break;
					
			case 4:	cout << "goodbye" << endl;
					table -> ~hashTable(); 
					break;
					
		}
		
	} while(menuChoice != 4);

	return 0;
}