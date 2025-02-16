/*
    title: cryptanalysis.cpp
    
    author: Jonah Perkins

    date: 2/10/2025

    description: 
    
    program to calculate the index of coincidence to determine the
    vigenere cipher key or to calculate the correlation of frequency to determine
    the caesar cipher key

    **this is by no means an efficient program, but it gets the job done**
*/
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

char shiftLetter(char c, int shift);

int main(){

    string cipherText;
    string plainText;
    string noSpaces;
    double ioc = 0;
    double frequencies[26] = {0};
    double englishFreq[26] = {
        0.0834, 0.0154, 0.0273, 0.0414, 0.1260, 0.0203, 0.0192, 0.0611, 0.0671, 0.0023, 
        0.0087, 0.0424, 0.0253, 0.0680, 0.0770, 0.0166, 0.0009, 0.0568, 0.0611, 0.0937, 
        0.0285, 0.0106, 0.0234, 0.0020, 0.0204, 0.0006
    };
    double cofList[26] = {0}; 
    double topFour[4][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
    int length = 0;
    int keyLen = -1;
    string key = "";
    int answer = -1;
    

    // get ciphertext
    cout << "Please enter the ciphertext (capital only): ";
    getline(cin, cipherText);
    

    noSpaces = cipherText;
    noSpaces.erase(remove(noSpaces.begin(), noSpaces.end(), ' '), noSpaces.end());
    length = noSpaces.length();
    plainText = noSpaces;

    while (answer < 1 || answer > 2)
    {
        cout << endl << "Please choose the type of cipher to solve:" << endl;
        cout << "       1. Caesar Cipher" << endl;
        cout << "       2. Vigenere Cipher" << endl;
        cout << "Selection (1 or 2): ";
        cin >> answer;
    }
    

    if (answer == 1)
    {
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
        char ch;
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
    }
    else if (answer == 2)
    {
        for (int i = 0; i < length; i++)
        {
            if (noSpaces[i] >= 'A' && noSpaces[i] <= 'Z')
            {
                frequencies[noSpaces[i]-'A']++;
            }
        }
        
        // calculate ioc
        for (int i = 0; i < 26; i++)
        {
            ioc += frequencies[i] * (frequencies[i]-1);
        }
        ioc = ioc / (length * (length - 1));

        bool again = true;
        string repeat = "";
        while (again)
        {
            
            cout << endl << "The ic of the cipher text is: " << ioc << endl;
            while (keyLen < 1)
            {
                cout << endl << "What would you like you key size to be? (>0)";
                cin >> keyLen;
                cout << endl;
            }
            

            vector<string> alphabets(keyLen, "");

            for (int i = 0; i < length; i++)
            {
                alphabets[i % keyLen] += noSpaces[i];
            }

            for (int i = 0; i < keyLen; i++)
            {
                double alphFreq[26] = {0};
                int countFreq[26] = {0};
                double aioc = 0;
                char ch;
                cout << endl << "alphabet " << i + 1 << ": " << alphabets[i] << endl;
                // get the frequency of each letter in the current alphabet
                for (int j = 0; j < alphabets[i].length(); j++)
                {
                    if (alphabets[i][j] >= 'A' && alphabets[i][j] <= 'Z')
                    {
                        alphFreq[alphabets[i][j]-'A'] += 1.0 / alphabets[i].length();
                        countFreq[alphabets[i][j]-'A']++;
                    }
                }

                cout << endl << "Frequencies:";
                for (int j = 0; j < 26; j++)
                {
                    char ch = 'A' + j;
                    cout << " " << ch;
                }
                cout << endl << "            ";
                for (int j = 0; j < 26; j++)
                {
                    cout << " " << countFreq[j];
                }
                cout << endl;

                // get the correlation of frequency for each possible key
                for (int k = 0; k < 26; k++)
                {
                    for (int j = 0; j < 26; j++)
                    {
                        if (alphFreq[j] > 0)
                        {
                            cofList[k] += alphFreq[j]*englishFreq[((26 + j - k) % 26)];
                        }
                    }
                }

                int alphLength = alphabets[i].length();
                // find the ioc for each alphabet
                for (int j = 0; j < 26; j++)
                {
                    aioc += countFreq[j] * (countFreq[j]-1);
                }
                aioc = aioc / (alphLength * (alphLength - 1));

                cout << endl << "The ic of the alphabet is is: " << aioc << endl;

                // find the highest 4 values; innefficient but it works :) 
                for (int k = 0; k < 26; k++)
                {
                    int j = 0;
                    bool inserted = false;
                    while(j < 4 && !inserted)
                    {
                        if (cofList[k] > topFour[j][0])
                        {
                            if (j < 3)
                            {
                                for (int x = 3; x > j; x--)
                                {
                                    topFour[x][0] = topFour[x-1][0];
                                    topFour[x][1] = topFour[x-1][1];
                                }
                            }
                            topFour[j][0] = cofList[k]; // stores value
                            topFour[j][1] = k; // stores associated key
                            inserted = true;
                        }
                        j++;
                    }
                }

                cout << endl << "Top 4 values:" << endl << endl;
                // convert the ciphertext using the highest 4 values to find solution
                for (int k = 0; k < 4; k++)
                {
                    char let = topFour[k][1] + 'A';
                    cout << "i = " << let << "   cof = " << topFour[k][0] << endl;
                    cout << "plaintext: ";
                    for (int j = 0; j < alphabets[i].length(); j++)
                    {
                        ch = alphabets[i][j];
                        if (ch != ' ')
                        {
                            cout << shiftLetter(ch, static_cast<int>(topFour[k][1])); // prints the shifted character
                        }
                        else
                        {
                            cout << " "; // otherwise, prints a space
                        }
                        
                    }
                    cout << endl;
                }
            }
        
            cout << endl << "What is the key (capital only)? ";
            cin >> key;
            while(key.length() != keyLen)
            {
                cout << endl << "Length does not match the number of alphabets." << endl;
                cin >> key;
            }

            //shift each letter by the correct character
            for (int i = 0; i < keyLen; i++)
            {
                int offset = key[i] - 'A';
                for (int j = i; j < length; j+= keyLen)
                {
                    plainText[j] = shiftLetter(noSpaces[j], offset);
                }
            }

            cout << endl << "Plaintext: " << plainText;

            while (repeat != "y" && repeat != "n")
            {
                cout << endl << "Would you like to try a different key length or key (y/n)? ";
                cin >> repeat;
            }
            if(repeat == "y")
            {
                again = true;
                repeat = "";
                keyLen = -1;
            }
            else
            {
                again = false;
            }
        }

    }

    return 0;
}

char shiftLetter(char c, int shift) {
    return 'A' + (c - 'A' - shift + 26) % 26;
}