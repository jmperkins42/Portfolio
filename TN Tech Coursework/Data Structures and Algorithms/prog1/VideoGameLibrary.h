/*
    title: VideoGameLibrary.h
    description: header file to the VideoGameLibrary class, which stores VideoGame variables in an
    array, allowing you to display the current games in the array, add and remove video games, and
    load and save video games to and from a file
*/
#ifndef VIDEOGAMELIBRARY_H
#define VIDEOGAMELIBRARY_H

#include <iostream>
#include <string>
#include <fstream>
#include "Text.h"
#include "VideoGame.h"
using namespace std;

class VideoGameLibrary
{
    private:
        VideoGame** videoGamesArray; // array that holds the video games
        int maxGames; // maximum capacity of the array
        int numGames; // current video games in the array
    public:
        void resizeVideoGameArray(); // doubles the array size if the current capacity is reached
        VideoGameLibrary(int); // constructor
        ~VideoGameLibrary(); // destructor
        void addVideoGameToArray(); // manually adds a video game to the library
        void displayVideoGames(); // prints all the video games to the screen
        void displayVideoGameTitles(); // prints all the video game titles to the screen
        void loadVideoGamesFromFile(string); // loads video games from a file
        void removeVideoGameFromArray(); // removes a video game from the array
        void saveToFile(string); // saves all the current video games in the array to a file
};
#endif