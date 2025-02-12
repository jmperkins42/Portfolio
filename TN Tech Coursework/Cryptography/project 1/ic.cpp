/*
    title: ic.cpp
    author: Jonah Perkins
    date: 2/10/2025
    description: program to calculate the index of coincidence to determine the vigenere cipher key
*/
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(){

    string cipherText;
    string noSpaces;
    double ioc = 0;
    int frequencies[26] = {0};
    int length = 0;
    int keyLen = -1;
    

    // get ciphertext
    cout << "Please enter the ciphertext (capital only): ";
    getline(cin, cipherText);
    

    for (int i = 0; i < cipherText.length(); i++)
    {
        if (cipherText[i] >= 'A' && cipherText[i] <= 'Z')
        {
            frequencies[cipherText[i]-'A']++;
        }
    }

    noSpaces = cipherText;
    noSpaces.erase(remove(noSpaces.begin(), noSpaces.end(), ' '), noSpaces.end());
    length = noSpaces.length();
    
    // calculate ioc
    for (int i = 0; i < 26; i++)
    {
        ioc += frequencies[i] * (frequencies[i]-1);
    }
    ioc = ioc / (length * (length - 1));

    cout << endl << "The ic of the cipher text is: " << ioc << endl;
    while (keyLen < 1)
    {
        cout << endl << "What would you like you key size to be? (>0)";
        cin >> keyLen;
        cout << endl;
    }
    

    string alphabets[keyLen] = {""};

    for (int i = 0; i < length; i++)
    {
        alphabets[i % keyLen] += noSpaces[i];
    }

    for (int i = 0; i < keyLen; i++)
    {
        cout << endl << "alphabet " << i + 1 << ": " << alphabets[i] << endl;
    }

    return 0;
}