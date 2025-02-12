/*
    title: VideoGame.h
    description: header file to the VideoGame class, which stores text variables 
    representing the different attributes of a video game, as well as an int for
    the year
*/

#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include "Text.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class VideoGame
{
    private: // includes the different attributes of a video game
        Text* title; // holds the game title
        Text* developer; // holds the game developer
        Text* publisher; // holds the game publisher
        int year; // holds the year the game was released
    public:
        VideoGame(Text*, Text*, Text*, int); // constructor
        ~VideoGame(); // destructor
        void printVideoGameDetails(); // prints the different attributes to the screen
        void printVideoGameDetailsToFile(fstream&); // prints the different attributes to a file
        Text* getVideoGameTitle(); // returns the text pointer to the video game's title
};

#endif