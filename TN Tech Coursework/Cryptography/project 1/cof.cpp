/*
    title: cof.cpp
    author: Jonah Perkins
    date: 2/10/2025
    description: program to calculate the correlation of frequency to determine the caesar cipher key
*/

#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

char shiftLetter(char c, int shift);

int main(){
    
    // variables
    string cipherText;
    double frequencies[26] = {0};
    double englishFreq[26] = {
    0.0834, 0.0154, 0.0273, 0.0414, 0.1260, 0.0203, 0.0192, 0.0611, 0.0671, 0.0023, 
    0.0087, 0.0424, 0.0253, 0.0680, 0.0770, 0.0166, 0.0009, 0.0568, 0.0611, 0.0937, 
    0.0285, 0.0106, 0.0234, 0.0020, 0.0204, 0.0006
};
    double cofList[26] = {0}; 
    double topFour[4][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
    int spaceCount;
    char ch;

    // get ciphertext
    cout << "Please enter the ciphertext (capital only): ";
    getline(cin, cipherText);

    // get the length no including spaces
    string noSpaces = cipherText;
    noSpaces.erase(remove(noSpaces.begin(), noSpaces.end(), ' '), noSpaces.end());
    int length = noSpaces.length();

    // get the frequency of each letter in the cipherText
    for (int i = 0; i < cipherText.length(); i++)
    {
        if (cipherText[i] >= 'A' && cipherText[i] <= 'Z')
            frequencies[cipherText[i]-'A'] += 1.0 / length;
    }

    // get the correlation of frequency for each possible key
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (frequencies[j] > 0)
            {
                cofList[i] += frequencies[j]*englishFreq[((26 + j - i) % 26)];
            }
        }
    }

    // find the highest 4 values; innefficient but it works :) 
    for (int i = 0; i < 26; i++)
    {
        int j = 0;
        bool inserted = false;
        while(j < 4 && !inserted)
        {
            if (cofList[i] > topFour[j][0])
            {
                if (j < 3)
                {
                    for (int x = 3; x > j; x--)
                    {
                        topFour[x][0] = topFour[x-1][0];
                        topFour[x][1] = topFour[x-1][1];
                    }
                }
                topFour[j][0] = cofList[i]; // stores value
                topFour[j][1] = i; // stores associated key
                inserted = true;
            }
            j++;
        }
    }

    cout << endl << "Top 4 values:" << endl << endl;
    // convert the ciphertext using the highest 4 values to find solution
    for (int i = 0; i < 4; i++)
    {
        cout << "i = " << topFour[i][1] << "   cof = " << topFour[i][0] << endl;
        cout << "plaintext: ";
        for (int j = 0; j < cipherText.length(); j++)
        {
            ch = cipherText[j];
            if (ch != ' ')
            {
                cout << shiftLetter(ch, static_cast<int>(topFour[i][1])); // prints the shifted character
            }
            else
            {
                cout << " "; // otherwise, prints a space
            }
            
        }
        cout << endl;
    }

    return 0;
}

// simple function to print the shifted letter
char shiftLetter(char c, int shift) {
    return 'A' + (c - 'A' + shift) % 26;
}