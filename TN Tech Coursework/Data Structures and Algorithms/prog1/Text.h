/*
    title: Text.h
    description: header file to the text class, which stores text information
    relevant to the VideoGame and VideoGameLibrary classes in a c-string
*/

#ifndef TEXT_H
#define TEXT_H

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

class Text
{
    private: 
        char* textArray; //pointer to constant character array
        int textLength; //integer representing the number of characters in textArray
    public:    
        Text(string); //constructor
        ~Text(); // destructor
        void displayText(); //prints text
        char* getText(); // returns text
        int getLength(); // returns text length
};

#endif