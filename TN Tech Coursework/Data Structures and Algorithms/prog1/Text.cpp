/*
    title: Text.cpp
    description: cpp file to the text class, which stores text information
    relevant to the VideoGame and VideoGameLibrary classes in a c-string
*/
#include "Text.h"

/*
    Text constructor: dynamically allocates a new char array and sets textArray
    equal to the new array.
*/ 
Text::Text(string str)
{
    char* charArray;
    charArray = new char[str.length() + 1];
    strcpy(charArray, str.c_str()); // copies the contenets of the string to the new array
    this -> textArray = charArray;
    this -> textLength = str.length();
}

/*
    Text destructor: deletes the allocated memory for textArray
*/
Text::~Text()
{
    delete this -> textArray;
    cout << "\nText destructor: Released memory for textArray.";
}

/*
    displayText() function: prints out the text from the textArray to the screen
*/
void Text::displayText()
{
    cout << this -> textArray;
}     

/*
    getText() function: returns the text from textArray
*/
char* Text::getText()
{
    return this -> textArray;
}

/*
    getLength() function: returns the length of the text in textArray
*/
int Text::getLength()
{
    return this -> textLength;
}