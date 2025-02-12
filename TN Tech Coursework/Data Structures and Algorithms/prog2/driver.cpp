/*
	title: driver.cpp
	author: Jonah Perkins
	date: 3/7/23
	purpose: driver file for CSC 1310 program 2
*/
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include "County.h"
#include "List.h"		//include your list header here------------------------------------------------------------------------

using namespace std;

int main()
{
	ifstream file;
	stringstream temp;
	string line, county, state;
	int index, pop;
	file.open("counties_list.csv", ios::in);
	//file.open("counties_ten.csv", ios::in);

	List<County*> list;		//create a new list of county pointers ------------------------------------------------------------------
	County* newCounty;

	if(file.good()) {
	while(getline(file, line, ','))
	{
		temp.clear();
		temp.str(line);
		temp >> index;

		getline(file, line, ',');
		county = line;

		getline(file, line, ',');
		state = line;

		getline(file, line, '\n');
		temp.clear();
		temp.str(line);
		temp >> pop;

		newCounty = new County(index, county, state, pop);
		list.append(newCounty);		//append newCounty to your list-----------------------------------------------------------------------------------
	}}

	file.close();

	list.mergesort();//call mergesort---------------------------------------------------------------------------------------------
	list.print();//print the list-----------------------------------------------------------------------------------------------------

	return 0;
}