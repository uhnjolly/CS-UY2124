
//
//  aj2389.cpp
//  aj2389
//
//  Created by Anjali James on 11/16/19.
//  Copyright © 2019 Anjali James. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Noble {
private:
    string name;
};

class StrengthToFight:Noble {
public:
    
    ostream& operator=(ostream& os) {
        os<< " Uggh!" << endl;
        return os;
    }
private:
    int strength;
    string name;
};

class Lord;

class Protector {
private:
    string name;
    int strength;
    Lord* myLord;
public:
    bool amIHired() const {
        if (myLord != nullptr) {
            return true;
        }
        return false;
    }
    
    int getStrength() const {return strength;}
};

class Archer:Protector {
    
}


class Lord:Noble {
private:
    string name;
    vector<Protector*> myArmy;
public:
    Lord(const string& name): name(name) {}
    int getArmyStrength() const {
        int size = 0;
        for (size_t i = 0;  i < myArmy.size(); i++){
            
        }
        return size;
    }
    bool Hire(const Protector& recruit) const {
        //check if u are not alive
        //check if protector is not alive
        // check if protector is already hired
        if (recruit.amIHired() == false) {
            if (recruit.getStrength()!=0){
                if (getArmyStrength()!=0) {
                    myArmy.push_back(&recruit);
                    return true;
                }
            }
        }
        return false;
    }
    
    
    
};

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}
