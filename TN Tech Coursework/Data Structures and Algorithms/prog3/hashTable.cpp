/*
    title: hashTable.cpp
    author: Jonah Perkins
    date: 4/3/23
    purpose: holds the functions for the hashTable class
*/

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "hashTable.h"
using std::string;
using std::cout;

/*
	function name:  hashTable constructor
	purpose: creates a new array of entry pointers, sets them to null, and seeds
	the random number generator
*/
hashTable::hashTable(int size)
{
	tableSize = size;
	hashArray = new entry*[tableSize]; // dynamically allocates new array
	for (int i = 0; i < size; i++) // sets all elements to NULL
	{
		hashArray[i] = NULL;
	}
	srand (time(0));	//this needs to be in the constructor, otherwise every user gets the same salt
}

/*
	function name: hashTable destructor
	purpose: deletes every user from the hash table by deleting the linked list
	in every bucket
*/
hashTable::~hashTable()
{
	for (int i = 0; i < tableSize; i++) // traverses the first entry in all buckets
	{
		while (hashArray[i] != NULL) // deletes any entry that isn't NULL
		{
			entry* temp = hashArray[i];
			hashArray[i] = hashArray[i] -> next;
			delete temp;
		}
	}
	delete hashArray; // deletes the hashArray
}

/*
	function name: getSalt
	purpose: used to append the salt to a password before we hash it
	*/
string hashTable::getSalt(string user)
{
	entry* temp = getEntry(user); // finds the user if they exist
	if (temp == NULL)
		return ""; // if not found, salt is NULL
	else
	{
		return temp -> getSalt(); // if found, salt is returned
	}
}

/*
	function name: addEntry
	purpose: to add a new user to the table
*/
void hashTable::addEntry(string uname, string salt, string passHash)
{
	int index = hash(uname); // finds where the new entry will go in the hashtable
	entry* temp = hashArray[index]; // creates a temporary entry pointer to make our way through the bucket's list
	if (getEntry(uname)) // checks to see if an entry with this username already exists
	{
		cout << "Username already exists\n"; // informs the user that the user already exists
	}
	else
	{	
		entry* newEntry = new entry(uname, salt, passHash); // creates a new entry, only if an entry with the given username doesn't exist
		if (temp == NULL) // if the first item in the bucket is null, we add the entry here
		{
			hashArray[index] = newEntry;
		}
		else
		{
			while (temp -> next) // traverses the list until we reach a NULL entry
			{
				temp = temp -> next;
			}
			temp -> next = newEntry;
		}
	}
}

/*
	function name: validateLogin
	purpose: to check if the user has entered the correct login credentials
*/
bool hashTable::validateLogin(string uname, string passHash)
{
	entry* temp = getEntry(uname); // finds the entry object 
	if (temp == NULL)
		return false;
	if (temp -> getHashedpwd() == passHash) // compares the given hashed password to the one on file
		return true;
	return false;
}

/*
	function name: removeUser
	purpose: to remove a user from the hash table
*/
bool hashTable::removeUser(string uname, string passHash)
{
	entry* temp = getEntry(uname); // finds the user if they exist
	if (temp == NULL) // ends the program if they don't exist
		return false;
	else if(validateLogin(uname, passHash)) // validates the login before deleting it
	{
		bool first = false; // bool indicating if the entry is the first in a bucket
		int index; // holds the bucket index
		for (int i = 0; i < tableSize; i++) // checks to see if the entry is first in a bucket
		{
			if (hashArray[i] == temp)
			{
				index = i; 
				first = true;
			}
		}

		if (first) // if it is the first in a bucket, it sets the new head to the next entry
		{
			hashArray[index] = temp -> next;
		}
		else // if not, it finds the previous entry to the one being removed and sets it's next to the delete entry's next
		{
			index = hash(uname); // finds correct bucket
			entry* prev = hashArray[index]; // entry pointer for the previous entry
			while (prev -> next != temp) // finds the previous entry
			{
				prev = prev -> next; 
			}
			prev -> next = temp -> next; // makes the connection
		}
		delete temp; // deletes the entry
		return true;
	}
	else
	{
		return false;
	}
}

/*
	function name: getEntry
	purpose: retrive a user for use in other functions
*/
hashTable::entry* hashTable::getEntry(string user)
{
	int index; // holds the bucket number for our key
	index = hash(user); // gets the bucket number
	entry* temp = hashArray[index];
	while (temp) // while the given entry is not NULL, we traverse through the bucket's list
	{
		if (temp -> getUsername() == user) // if given entry's username matches the one we are looking for, we return it
		{
			return temp;
		}
		temp = temp -> next; // moves to the next entry
	}
	return NULL; // if we don't find the entry, we return NULL
}

//don't touch this!
int hashTable::hash(string key)
{
	int sum = 0;
	for(int i = 0; i < key.size(); i++)
		sum += key[i];
	
	return sum % tableSize;
}

//don't touch this!
string hashTable::generateSalt()
{
	string s = "";
	
	for(int i = 0; i < tableSize; i++)
		s = s + char('!' + (rand() % 93));
	return s;
}