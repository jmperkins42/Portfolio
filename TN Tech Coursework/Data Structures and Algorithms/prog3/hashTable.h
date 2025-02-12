/*
    title: hashTable.h
    author: Jonah Perkins
    date: 4/3/23
    purpose: holds the function prototypes for the hashTable class and 
	function definitions for the entry class
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
using std::string;

class hashTable
{
	private:
		class entry;
		//add the attributes you need for the class---------------------------------------------------------
		int tableSize;
		entry** hashArray;
		entry* getEntry(string);
		int hash(string);
	public:
		//add all the functions you need--------------------------------------------------------------------
		hashTable(int);
		~hashTable();
		string generateSalt();
		string getSalt(string);
		void addEntry(string, string, string);
		bool validateLogin(string, string);
		bool removeUser(string, string);
};

class hashTable::entry
{
	private:
		string uname;
		string salt;
		string passHash;
	public:
		entry* next;
		//constructor
		entry(string unameA, string saltA, string passHashA) // assigns each attribute and sets next to NULL
		{
			uname = unameA;
			salt = saltA;
			passHash = passHashA;
			next = NULL;
		}
		// getter functions
		string getUsername() // returns the username
		{
			return uname;
		}
		string getSalt() // returns the salt
		{
			return salt;
		}
		string getHashedpwd() // returns the hashed password
		{
			return passHash;
		}
};

#endif