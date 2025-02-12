/*
    title: VideoGameLibrary.cpp
    description: cpp file to the VideoGameLibrary class, which stores VideoGame variables in an
    array, allowing you to display the current games in the array, add and remove video games, and
    load and save video games to and from a file
*/
#include "VideoGameLibrary.h"
#include "VideoGame.h"
#include "Text.h"

/*
    resizeVideoGameArray() function: doubles the size of the videoGamesArray when the maximum capacity 
    of the array has been reached (numGames == maxGames). The function dynamically allocates a new array
    twice the size of the previous and adds each video game from the previous to it, finally setting the
    videoGamesArray equal to it.
*/
void VideoGameLibrary::resizeVideoGameArray()
{
    VideoGame** newLibrary = new VideoGame*[this -> maxGames*2]; //creates the new array double the size
    for (int i = 0; i < this -> numGames; i++) // copies all the current elements into the new array
    {
        newLibrary[i] = this -> videoGamesArray[i];
    }
    this -> videoGamesArray = newLibrary; // sets the old array equal to the new
    cout << "Resizing VideoGameArray from " << this -> maxGames << " to " << this -> maxGames*2 << ".\n";
    this -> maxGames *=2;
}

/*
    VideoGameLibrary constructor: dynamically allocates a videoGamesArray the size of the int parameter, setting
    the maxGames equal to the parameter and setting numGames to 0
*/
VideoGameLibrary::VideoGameLibrary(int maxVG)
{
    this -> videoGamesArray = new VideoGame*[maxVG];
    this -> maxGames = maxVG;
    this -> numGames = 0;
}

/*
    VideoGameLibrary destructor: releases memory for each videogame in the array and then deletes the array itself
*/
VideoGameLibrary::~VideoGameLibrary()
{
    for (int i = 0; i < this -> numGames; i++)
    {
        videoGamesArray[i] -> ~VideoGame(); // calls the VideoGame destructor before deleting the VideoGame itself
        delete videoGamesArray[i];
    }
    delete [] videoGamesArray; // deletes the VideoGameLibrary object
    cout << "\nVideoGameLibrary destructor: Released memory for each game in the video game array and the array itself.\n";
}

/*
    addVideoGameToArray() function: allows the user to manually input a video game into the array
*/
void VideoGameLibrary::addVideoGameToArray()
{
    //variables
    string t;
    string d;
    string p;
    int year;
   
    //gets data for the VideoGame
    cout << "\nVideo Game TITLE: ";
    getline(cin, t);
    cout << "\nVideo Game DEVELOPER: ";
    getline(cin, d);
    cout << "\nVideo Game PUBLISHER: ";
    getline(cin, p);
    cout << "\nVideo Game YEAR: ";
    cin >> year;
    cin.ignore();
    Text* title = new Text(t);
    Text* dev = new Text(d);
    Text* pub = new Text(p);
    
    // dynamically allocates a new VideoGame object using the given data
    VideoGame* newGame = new VideoGame(title, dev, pub, year);
    if (numGames == maxGames) // if the current capacity is reached, the array will resize itself
        this -> resizeVideoGameArray();
    this -> videoGamesArray[numGames] = newGame; // puts the VideoGame in the next available spot
    numGames++; // increments numGames
}

/*
    displayVideoGames() function: displays all current VideoGames held in the library 
*/
void VideoGameLibrary::displayVideoGames()
{
    cout << endl;
    for (int i = 0; i < numGames; i++)
    {
        cout << "\n\t\t\t\t----------Video Game " << i + 1 << "----------";
        videoGamesArray[i] -> printVideoGameDetails();
    }
    cout << endl;
}

/*
    displayVideoGameTitles() function: displays only the titles of all current VideoGames
    held in the library so that the user can decide which one they want to remove
*/
void VideoGameLibrary::displayVideoGameTitles()
{
    for (int i = 0; i < numGames; i++)
    {
        cout << "\nVideo Game " << i + 1 << ": ";
        videoGamesArray[i] -> getVideoGameTitle() -> displayText();
    }
}

/*
    loadVideoGamesFromFile() function: loads in VideoGames from a file and adds them to the 
    library. It uses a filestream object to read in the different attributes before dynamically
    allocating a new VideoGame object which gets added to the next available spot in the array,
    which gets resized if more space is needed
*/
void VideoGameLibrary::loadVideoGamesFromFile(string fileName)
{
    string t;
    string d;
    string p;
    string y;
    fstream iofile;
    iofile.open(fileName); // attempts to open the file the user inputted
    if (iofile.is_open()) // if the file is open, it will continue and read through it
    {
        while (iofile.peek() != EOF)
        {
            getline(iofile, t); // gets title
            Text* nTitle = new Text(t); 
            getline(iofile, d); // gets developer
            Text* nDev = new Text(d);
            getline(iofile, p); // gets publisher
            Text* nPub = new Text(p);
            getline(iofile, y); // gets year
            VideoGame* nVideoGame = new VideoGame(nTitle, nDev, nPub, stoi(y)); // dynamically allocates new VideoGame object
            if (this -> numGames == this -> maxGames)
                this -> resizeVideoGameArray(); // resizes if necessary
            this -> videoGamesArray[numGames] = nVideoGame; // adds it to the library
            this -> numGames++; 
            cout << t << " was added successfully\n";
        }
        iofile.close();  // closes file
    }
    else
    {
        cout << "Sorry, I was unable to open the file.\n"; // occurs if the fileName does not match one in the folder
    }
}


/*
    removeVideoGameFromArray() function: assuming that numGames is at least 1, the function will remove the desired VideoGame
    object from the array after a list of all the game titles is printed. If the removed game isn't the only game or the final
    game, the function will then move all the video games above it down a spot.
*/
void VideoGameLibrary::removeVideoGameFromArray()
{
    if (numGames < 1) // makes sure there is at least one game in the library
    {
        cout << "\nThere must be at least one video game in the library.\n";
        return;
    }
    int remove = -1;
    cout << "\nChoose from the following video games to remove:\n";
    this -> displayVideoGameTitles(); // displays video game titles
    cout << "\nChoose a video game to remove between 1 & " << numGames << ":  ";
    cin >> remove; // gets the number of the game the user wants to remove
    cin.ignore();
    if (remove >= 1 && remove <= numGames) // if the removed game wasnt the only game ore the final game, the games above it will move down one spot
    {
        string name = videoGamesArray[remove-1] -> getVideoGameTitle() -> getText();
        this -> videoGamesArray[remove-1] -> ~VideoGame();
        if (numGames != 1 && this -> numGames != remove)
        {
            for (int i = remove; i < numGames; i++)
            {
                this -> videoGamesArray[i-1] = this -> videoGamesArray[i];
            }
            this -> videoGamesArray[numGames-1] = NULL; // makes the top game null (removing the extra copy)
        }
        cout << "\nThe video game \"" << name << "\" has been successfully deleted.\n";
        this -> numGames--;
    }
    else
    {
        cout << "This is not a valid entry.\n"; // if the number inputted is invalid
    }
}

/*
    saveToFile() function: opens up the user's desired file (if able) and prints the video game details to the 
    file using the filestream object
*/
void VideoGameLibrary::saveToFile(string fileName)
{
    fstream iofile;
    iofile.open(fileName); // attempts to open the file
    if (iofile.is_open()) // if successful, the function will continue
    {
        for (int i = 0; i < this -> numGames; i++)
        {
            this -> videoGamesArray[i] -> printVideoGameDetailsToFile(iofile); // prints all the VideGame attributes on different lines
        }
        iofile.close(); // closes the file
        cout << "All video games in your library have been printed to " << fileName << endl;
    }
    else
    {
        cout << "Sorry, I was unable to open the file.\n"; // if unsuccessful , the function stops
    }
}