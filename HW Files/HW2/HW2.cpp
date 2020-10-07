//
//  main.cpp
//  hw02
//
//  Created by Anjali James on 9/19/19.
//  Copyright © 2019 Anjali James. All rights reserved.
//

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

struct Warrior {
    string name;
    int power;
};

void StWarrior(ifstream &file, vector<Warrior> &WarList, string &name, int strength ) {
    
    Warrior fighter;
    fighter.name = name;
    fighter.power = strength;
    WarList.push_back(fighter);
}

void WarriorStrength(const vector<Warrior> &mystrength) {
    cout << "there are " << mystrength.size() <<" "<< "Warrior" << endl;
    
    for (const Warrior& person : mystrength)
    {
        cout << "Warrior: " << person.name << ", " << "Strength: " << person.power << endl;
    }
}

void Battle(Warrior& fightOne, Warrior& fightTwo)
{
    cout << fightOne.name << " Battles " << fightOne.name << endl;
    if (fightOne.power < fightTwo.power) {
        if (fightOne.power<=0) { cout << "He is dead " << fightTwo.name<<endl; }
        
        else {
            fightTwo.power -= fightOne.power;
            fightOne.power = 0;
        }
    }
    else if (fightOne.power <= 0 && fightTwo.power <= 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    
    else if (fightOne.power == fightTwo.power) {
        /// checks to see if powers are equals
        cout << "Mutual Annihalation:" << fightOne.name << " and " << fightTwo.name
        << " die at each other's hands" << endl;
        fightOne.power = 0;
        fightTwo.power = 0;
    }
    else {
        if (fightTwo.power < fightOne.power) {
            if (fightTwo.power <= 0) {
                cout << "He's dead " << fightOne.name<<endl;
            }
            else {
                fightOne.power -= fightTwo.power;
                fightTwo.power = 0;
            }
        }
    }
}

int PotentialWarrior(const vector<Warrior> &fightList, const string &name)
{
    for (int i = 0; i < fightList.size(); i++) {
        if (fightList[i].name == name){
            return i;
        }
        
    }
    return fightList.size();
}

int main() {
    ifstream WFile("Warriors.txt");
    if (!WFile) { cerr << "can't open file\n"; exit(2); }
    string transW;
    string fightOne;
    string fightTwo;
    int strength;
    vector<Warrior>myWar;
    while (WFile >> transW)
    {
        if (transW == "Warrior") {
            string WarriorName;
            string WarriorName2;
            int strength;
            WFile >> WarriorName >> strength;
            StWarrior(WFile, myWar, WarriorName, strength);
        }
        if (transW == "Status") {
            WarriorStrength(myWar);
        }
        if (transW== "Battle") {
            
            WFile >> fightOne;
            WFile >> fightTwo;
            int tempOne= PotentialWarrior(myWar, fightOne);
            int tempTwo= PotentialWarrior(myWar, fightTwo);
            Battle(myWar[tempOne],myWar[tempTwo]);
            
            
            
        }
        
    }
}
