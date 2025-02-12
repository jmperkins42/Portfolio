/*
    title: VideoGame.cpp
    description: cpp file to the VideoGame class, which stores text variables 
    representing the different attributes of a video game, as well as an int for
    the year
*/
#include "VideoGame.h"
#include "Text.h"

/*
    VideoGame constructor: allocates 3 text pointers and an int to a VideoGame object
*/
VideoGame::VideoGame(Text* title, Text* dev, Text* pub, int year)
{
    this -> title = title;
    this -> developer = dev;
    this -> publisher = pub;
    this -> year = year;
}

/*
    VideoGame destructor: deletes each text variable associated with the VideoGame attributes
    and prints an update to the screen when this is finished
*/
VideoGame::~VideoGame()
{
    // uses the text destructor
    title -> ~Text();
    developer -> ~Text();
    publisher -> ~Text();
    cout << "\nVideoGame destructor: Released memory for VideoGame object.";
}

/*
    printVideoGameDetails() function: prints the different attributes to the screen for the
    given VideoGame
*/
void VideoGame::printVideoGameDetails()
{
    cout << "\n\t\t   Game Title: ";
    title -> displayText();
    cout << "\n\t\t    Developer: ";
    developer -> displayText();
    cout << "\n\t\t    Publisher: ";
    publisher -> displayText();
    cout << "\n\t\tYear Released: " << year;
}   

/*
    printVideoGameDetailsToFile() function: prints the VideoGame attributes to the file stream 
    object parameter, which has the desired file open
*/
void VideoGame::printVideoGameDetailsToFile(fstream& iofile)
{
    iofile << title -> getText() << endl;
    iofile << developer -> getText() << endl;
    iofile << publisher -> getText() << endl;
    iofile << year << endl;
}   

/*
    getVideoGameTitle() function: returns the text object associated with the title of the given 
    VideoGame
*/
Text* VideoGame::getVideoGameTitle()
{
    return this -> title;
}              