//
//  main.cpp
//  hw03
//
//  Created by Anjali James on 9/25/19.
//  Copyright © 2019 Anjali James. All rights reserved.
//
//
// Created by Anjali James
//
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class Warrior {
    friend ostream&  operator<<(ostream& os, const Warrior& w);
public:
    Warrior(const string &Name, const string &weapon, int power) : name(Name), wp(weapon, power) {}
    void display() const { cout << "Name:" << name << endl; }
    const string &getName() const { return name; }
    // for the battle method, we are only passing in one fighter. AKA the person we are battling
    void MyBattle(Warrior& opponent) {
        cout << this->name<< " Battles " << opponent.name << endl;
        if (this->wp.getPower() < opponent.wp.getPower()) {
            if (this->wp.getPower()<=0) { cout << "He is dead " << opponent.name<<endl; }
            else {
                int x = this->wp.getPower()-opponent.wp.getPower();
                int L = 0;
                opponent.wp.setPower(x);
                this->wp.setPower(L);
            }
        }
        else if (this->wp.getPower() <= 0 && opponent.wp.getPower() <= 0) {
            // checks to see if powers are both less than or equal to zero
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (this->wp.getPower() == opponent.wp.getPower()) {
            /// checks to see if powers are equals
            int L = 0;
            cout << "Mutual Annihalation:" << this->name << " and " << opponent.name
            << " die at each other's hands" << endl;
            this->wp.setPower(L);
            opponent.wp.setPower(L);
        }
        else {
            if (opponent.wp.getPower() < this->wp.getPower()) {
                if (opponent.wp.getPower() <= 0) {
                    cout << "He's dead " << this->name<<endl;
                }
                else {
                    int loss = this->wp.getPower()- opponent.wp.getPower();
                    int L = 0;
                    this->wp.setPower(loss);
                    opponent.wp.setPower(L);
                }
            }
        }
    }
    
    
private:
    class Weapon {
    public:
        Weapon(const string &wType, int xp) : name(wType), wStrength(xp) {}
        void display() const { cout << "Weapon type" << name << "," << "Weapon strength" << wStrength << endl; }
        const string &getWeapName() const { return name; }
        int getPower() const { return wStrength; }
        void setPower(int xp) { wStrength = xp; }
    private:
        string name;
        int wStrength;
    };
    string name;
    Weapon wp;
};

//note: But the weapon is what actually holds the warrior's strength.

// Vector of type Warrior
void StoreWarrior(vector<Warrior> &WarriorHolder, const string &name, const string &wp,int strength) {
    // creates warrior based on information passed to function
    Warrior Man(name,wp,strength);
    WarriorHolder.push_back(Man);
}
// operator overloading
ostream&  operator<<(ostream& os, const Warrior& w){
    os << "Warrior:" << w.name;
    os << ", weapon: " << w.wp.getWeapName() << " , " << w.wp.getPower();
    return os;
}

void WarriorStats(const vector<Warrior> &list) {
    cout << "There are " << list.size() <<" "<< "Warrior" << endl;
    for (int i = 0; i < list.size(); ++i) {
        cout << list[i] << endl;
    }
}

size_t findWarrior(const string& name, const vector<Warrior>& WarHold) {
    for (size_t i = 0; i < WarHold.size(); ++i) {
        if (WarHold[i].getName() == name)
            return i;
    }
    return WarHold.size();
    // return size of vector when it is not found.
}


int main(){
    ifstream WarriorFile("warrior.txt");
    if (!WarriorFile) { cerr << "can't open file\n"; exit(2); }
    else {
        string word;
        vector<Warrior> Roster;
        while (WarriorFile >> word) {
            if (word == "Warrior") {
                string Name;
                string Weapon;
                int WpStrength;
                WarriorFile >> Name >> Weapon >> WpStrength;
                StoreWarrior(Roster, Name, Weapon, WpStrength);
            }
            if (word == "Status") {
                WarriorStats(Roster);
            }
            if (word == "Battle") {
                string FirstFight;
                string SecondFight;
                WarriorFile >> FirstFight;
                WarriorFile >> SecondFight;
                size_t firstWar = findWarrior(FirstFight,Roster);
                size_t secondWar = findWarrior(SecondFight,Roster);
                if (firstWar != Roster.size() and secondWar != Roster.size()) {
                    Roster[firstWar].MyBattle(Roster[secondWar]);
                    
                }
                
                
                
            }
        }
    }
}
