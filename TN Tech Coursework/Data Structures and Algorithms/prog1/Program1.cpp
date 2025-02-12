/*
    Name: Jonah Perkins
    Course: CSC 1310-001
    Due: 2/15/23
*/

#include "Text.h"
#include "VideoGame.h"
#include "VideoGameLibrary.h"
using namespace std;

int main()
{
    // variables

    int maxVG; // holds max number of video games
    int currVG = 0; // holds current number of video games
    VideoGameLibrary* library; // videoGameLibrary pointer
    int answer; // holds answer from menu
    bool again = true; // keeps the program running if answer != 6
    string fileName;

    // gets the max number of video games in the library and dynamically creates a VideoGameLibrary object
    cout << "How many video games can your library hold?\n";
    cin >> maxVG; 
    library = new VideoGameLibrary(maxVG);

    // menu that only stops if 6 is input
    while (again)
    {
        cout << "\nWhat would you like to do?\n";
        cout << "1.  Load video games from file.\n";
        cout << "2.  Save video games to a file.\n";
        cout << "3.  Add a video game.\n";
        cout << "4.  Remove a video game.\n";
        cout << "5.  Display all video games.\n";
        cout << "6.  Remove ALL video games from this Library and end program.\n";
        cout << "CHOOSE 1-6:  ";
        cin >> answer;
        cin.ignore();
        while (answer < 1 || answer > 7)
        {
            cout << "\nThat is not a valid choice.\n";
            cout << "CHOOSE 1-6:  ";
            cin >> answer;
            cin.ignore();
        }
        switch(answer)
        {
            case 1: // gets the name of the file and calls the loadVideoGamesFromFile() function
            cout << "\nWhat is the name of the file? (example.txt):  ";
            cin >> fileName;
            cin.ignore();
            library -> loadVideoGamesFromFile(fileName);
            break;

            case 2: // gets the name of the file and calls the saveToFile() function
            cout << "\nWhat is the name of the file? (example.txt):  ";
            cin >> fileName;
            cin.ignore();
            library -> saveToFile(fileName);
            break;

            case 3: // calls the addVideoGameToArray() function
            library -> addVideoGameToArray(); 
            break;

            case 4: // calls the removeVideoGameFromArray() function
            library -> removeVideoGameFromArray();
            break;

            case 5: // calls the displayVideoGames() function
            library -> displayVideoGames();
            break;

            case 6: // ends the program by calling again = false; and calls the ~VideoGameLibrary() destructor function
            again = false;
            library -> ~VideoGameLibrary();
            break;
        }
    }
    return 0;
}