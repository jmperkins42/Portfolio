/*
	title:	markovList.h
	author:	Jonah Perkins
	date:	4/26/2023
	purpose:	holds the markovList class and associated functions 
				implemented using a linked list
*/
#ifndef MARKOVLIST_H
#define MARKOVLIST_H

#include<map>
#include<fstream>
#include<sstream>
#include<iostream>
#include<stdlib.h>
using namespace std;

class markovList
{
	private:
		struct edge
		{
			float weight;
			string destination;
			edge* next;
		};
		int corpusSize;
		map<string, edge*> corpus;
	public:
		markovList(const char*);
		~markovList();
		string generate(int);
};

markovList::markovList(const char* filename)
{
	ifstream file(filename);
	stringstream parser, splitter;
	string line, index, word;
	float weight;
	edge* newEdge;
	int i = 0;
	srand (time(0));
	
	if(file.good()) {
	file >> corpusSize;
	file.ignore(1, '\n');
	
	while(getline(file, line, '\n')) //map every word to a position in the matrix, keep the line in an array of buffers for later
	{
		parser.clear();
		parser << line;
		getline(parser, index,',');	//pulls the first word of the line, which is the node for which we're making a list of neighbors
		newEdge = new edge;
		corpus[index] = newEdge; //initialize an empty list at the index---
		while(getline(parser, word, ','))
		{
			edge* nextEdge = new edge;	//allocate a new node in the edge list---
			
			splitter.clear();
			splitter.str(word);
			splitter >> word >> weight;

			newEdge -> weight = weight;	
			newEdge -> destination = word;	//stick word and weight on the node you've just allocated---
			newEdge -> next = nextEdge;
			newEdge = newEdge -> next;	//make sure your new node is attached to the list---
		}
	}}
}

markovList::~markovList()
{
	edge* temp;
	for (map<string, edge*>::iterator it = corpus.begin(); it != corpus.end(); ++it) // parses through all the elements in the map
	{
		temp = it -> second;
		while (temp -> next) // deletes each list
		{
			it -> second = temp -> next;
			delete temp;
		}
	}
}
		
string markovList::generate(int length)
{
	map<string, edge*>::iterator it = corpus.begin();	//initialize an iterator to find a random node in the next line
	advance(it,rand() % corpusSize);	//this grabs a random node from your corpus as a starting point
	string generation = ""; // holds the entire string we are returning
	edge* temp = it -> second;
	for (int i = 0; i < length; i++)
	{
		float roll = (float)rand()/RAND_MAX;
		float sum = 0; // to be checked against the roll
		string word = ""; // holds the word being added
		while (sum < roll)
		{
			sum += temp -> weight;
			if (sum > roll)
			{
				word = temp -> destination;
			}
			temp = temp -> next;
		}
		generation += word + " "; // adds the word to the string we are returning
		temp = corpus[word];
	}
	return generation;
}


#endif