/*
    Title:     program2.cpp
    Author:    Jonah Perkins
    Date:      11/1/23
    Purpose:   Traveling Salesman - find the lowest cost
                tour when traveling from US to 8 other countries
                and then back to US.
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include "GraphMatrix.h"
using namespace std;

const int SIZE = 10;
const string COUNTRY_CODES[SIZE]={"AU", "BR", "CA", "CN", "GL", "IT", "NA", "RU", "US", "US"};

/*
	Use the following structure to store each tour & its cost
	You will create an array of Tour variables in your program
*/
struct Tour
{
	string tour[SIZE];
	int cost;
};

//Function Prototypes
int searchCountryCode(string);
GraphMatrix* readFileMakeMatrix();
void printStringArray(string* arr, int size);
void lexicographic(string*, int, Tour*, GraphMatrix*);
void findLowest(Tour*);
void saveTour(string*, Tour*, int, GraphMatrix*);

int main()
{	
	Tour *tourOptions = new Tour[40320];
	//read in the flight information from the file and then create the weight matrix
	GraphMatrix * matrix = readFileMakeMatrix();
	string * countries = new string[SIZE-2];
	
	cout << "\n\n*************************COUNTRIES*******************\n";
	for(int x=0; x < SIZE-2; x++)
	{
		countries[x] = COUNTRY_CODES[x];
		cout << countries[x] << endl;
	}
	
	
	//generate all possible tours (starting & ending with "US") using lexicographic permute algorithm
	//you will need to call your lexicographic function, sending the modified countries array with the 8 country codes
	lexicographic(countries, SIZE-2, tourOptions, matrix);

	cout << "\n\n*************************SOLUTION*******************\n";
	//find the lowest cost tour and print it out (including the cost)
	findLowest(tourOptions);
	
	cout << "\nHappy Traveling!\n";
	
	//don't forget to release anything that was dynamically allocated!
	matrix->~GraphMatrix();
	delete [] countries;
	delete [] tourOptions;
	
	return 0;
}
/*
	Function: searchCountryCode
	Parameters: a string with the country code like "BR"
	Returns: an integer representing this country's index in the GraphMatrix.
	For example, if the parameter is "BR", it should return index 1.  If the parameter is "CA", it should return index 3
	It is returning the index value in the COUNTRY_CODES array.	
	Implement this search function with the binary search algorithm!
*/
int searchCountryCode(string cc)
{
	int left = 0; // hold left index
	int right = SIZE - 1; // holds right index
	int mid; // holds middle index that we compare to the country code
	while (left <= right) // continues while left and right have not passed each other
	{
		int mid = (left + right) / 2; // sets mid to the middle element in the array
		if (COUNTRY_CODES[mid] == cc) // checks to see if it matches
			return mid; // if so, we return that index
		else if (COUNTRY_CODES[mid] < cc) // If the code at mid comes before the cc alphabetically,
			left = mid + 1;				  // the new mid becomes the index after mid.
		else 				// Alternatively, if it comes after, then right becomes mid
			right = mid;	// this way the number of elements is being cut in half after
	}						// each iteration of the while loop.
	return -1; // just in case the code is not found, we return -1
}

/*
	Title: readFileMakeMatrix
	Purpose:  this function will read the data in flights.txt and create an
	adjacency matrix with the couuntry codes.  The matrix values will be the
	cost of the flights.
*/
GraphMatrix* readFileMakeMatrix()
{
	ifstream inFile;
	GraphMatrix * matrix = new GraphMatrix(SIZE-1);
	cout << "\nCreated the matrix.";
	string country1, country2;
	int price;
	inFile.open("flights.txt");
	cout << "\nReading from flights.txt\n";
	if(inFile)
	{
		while(inFile >> country1)
		{
			inFile >> country2;
			inFile >> price;
			//add price to graph matrix
			matrix->addEdge(searchCountryCode(country1), searchCountryCode(country2), price);
			cout << "\nAdded edge from " << country1 << " to " << country2 << " with cost of $" << price;
		}
	}
	else
		cout << "\nSorry, I am unable to open the file.\n";
	inFile.close();
	cout << "\n\nFLIGHT PRICE GRAPH MATRIX\n";
	matrix->printGraph();
	cout << endl;
	return matrix;
}

/*
	Title: printStringArray
	Purpose:  this function will print the array of strings with a space
		between each string
*/
void printStringArray(string* arr, int size)
{
	for(int x=0; x<size; x++)
	{
		cout << arr[x] << " ";
	}
}

/*
	Title: lexicographic
	Purpose:  this function will generate all permutations of the tour, print them to
	the screen and add them to the tour array
*/
void lexicographic(string* countries,int size, Tour* options, GraphMatrix* matrix)
{
	string* tempArr = countries;
	bool isDone = false;
	int iterationCount = 1;
	int lowBound = 0;		//The "i" value
	int uppBound = 0;		//The "j" value
	
	//Temporary variables to store values during a swap
	string tempStr;
	
	cout << "\nLEXICOGRAPHIC ALGORITHM";
	
	while(!isDone)
	{
		/*
			---PRINT TEMPSTRING---
		*/
		cout << "\n" << iterationCount << ":\t";
		printStringArray(tempArr, size); // prints the current permutation
		saveTour(tempArr, options, iterationCount-1, matrix); // saves the current permutation
		iterationCount++;
		/*
			---FIND lowBound OR DETERMINE IF DONE---
		*/
		isDone = true;
		for(int i = 0; i < size-1; i++)
		{
			if(tempArr[i]<tempArr[i+1])
			{
				isDone = false;
				lowBound = i;
			}
		}
		if(isDone)
			continue;
		/*
			---FIND uppBound---
		*/
		for(int j = size-1; j>0; j--)
		{
			if(tempArr[j] > tempArr[lowBound])
			{
				uppBound = j;
				break;
			}
		}
		/*
			---SWAP ELEMENTS---
		*/
		tempStr = tempArr[lowBound];
		tempArr[lowBound] = tempArr[uppBound];
		tempArr[uppBound] = tempStr;
		/*
			---REVERSE ELEMENTS FROM lowBound+1 TO l-1---
		*/
		for (int i = 1; lowBound+i<size-i; i++)
		{
			tempStr = tempArr[lowBound+i];
			tempArr[lowBound+i] = tempArr[size-i];
			tempArr[size-i] = tempStr;
		}
		
	}
	cout << "\nLexicographic Algorithm complete!";
}

/*
	Title: findLowest
	Purpose:  this function will loop through the entire tour array and find the
	one with the lowest cost, printing that to the screen
*/
void findLowest(Tour* options)
{
	Tour lowest = options[0]; // makes the first element the lowest
	for (int i = 1; i < (40320); i++) // loops through the entire array
	{
		if (options[i].cost < lowest.cost) // if the current permutation is cheaper, it becomes the new lowest
		{
			lowest = options[i]; 
			cout << "New Lowest is: " << lowest.cost << " with tour "; 
			printStringArray(lowest.tour, SIZE);
			cout << endl;
		}
	}
	cout << "\n\n****************************************************\n";
	cout << "The tour with the lowest cost of $" << lowest.cost << " is "; // tells the user the cheapest permutation
	printStringArray(lowest.tour, SIZE); // prints the permutation
}

/*
	Title: saveTour
	Purpose:  this function will add each permutation to the tour array, appending
	the US to the beginning and the end and find the cost of that tour by adding
	up all the edges.
*/
void saveTour(string* countries, Tour* options, int count, GraphMatrix* matrix)
{
	// add the permutation to it's respective spot in the tour array
	options[count].tour[0] = "US"; // US is appended to the beginning 
	for (int i = 1; i < SIZE-1; i++)
	{
		options[count].tour[i] = countries[i-1];
	}
	options[count].tour[SIZE-1] = "US"; // US is appended to the end
	for (int j = 0; j < SIZE-1; j++) // uses the graphmatrix to find the cost between each edge
	{
		cout << matrix->getWeight(searchCountryCode(options[count].tour[j]), searchCountryCode(options[count].tour[j+1])) << " ";
		options[count].cost += matrix->getWeight(searchCountryCode(options[count].tour[j]), searchCountryCode(options[count].tour[j+1]));
	}
	cout << " has tour weight: " << options[count].cost; // prints the total cost
}