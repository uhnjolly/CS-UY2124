//
//  main.cpp
//  hw01_2019
//
//  Created by Anjali James on 9/8/19.
//  Copyright © 2019 Anjali James. All rights reserved.
// This program reflects

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void deCryptStr(string& word,int step);
char deCryptChar(char letter, int step );

int main() {
    vector<string>storeV;
    //opens the file and checks it
    ifstream cFile("encrypt.txt");
    if (!cFile) {
        cerr << "Could not open the file.\n";
        exit(1);
    } else {
        int num;
        cFile >> num;
        string temp;
        getline(cFile, temp);
        string line;
        while (getline(cFile, line)) {
            deCryptStr(line, num);
            storeV.push_back(line);
        }
        size_t size = storeV.size();
        while (size >= 1) {
            cout << storeV[size-1] << endl;
            size--;
        }
    }
}
// funct that decrypts letter
char deCryptChar(char letter, int step ){
    if (!(letter < 97)){
        int deChar = letter - step;
        if(deChar >= 97 && deChar <= 122) {
            letter = char(deChar);
        }
        else if (deChar <97){
            letter = char(deChar + 26);
        }
    }
    return letter;
}

//funct that changes the word
void deCryptStr(string& word,int step){
    for (int i = 0; i < word.length(); ++i){
        if (word[i]!= ' ') {
            word[i] = deCryptChar(word[i], step);
        }
    }
}
