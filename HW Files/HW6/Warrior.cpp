//
//  Warrior.cpp
//  hw06
//
//  Created by Anjali James on 10/26/19.
//  Copyright © 2019 Anjali James. All rights reserved.
//

#include "Warrior.hpp"
#include "Noble.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace WarriorCraft {
    Warrior::Warrior(const string& name, double warriorStrength) : name(name), strength(warriorStrength) {}
    
    void Warrior::modifyStrength(double ratio) {
        strength -= (strength * ratio);
    }
    
    void Warrior::display() const {
        cout << name << ": " << strength << endl;
    }
    
    const Noble* Warrior::getOwner() const { return master; }
    
    // points to the noble that hired the warrior
    void Warrior::assignOwner(Noble* noblePtr) {
        master = noblePtr;
    }
    
    const string Warrior::getName() const { return name; }
    
    const int Warrior::getStrength() const { return strength; }
    
    bool Warrior::runaway() {
        cout << name << " flees in terror, abandoning his lord, " << master->getName() << endl;
        if (master != nullptr) {
            master->removeWarrior(this);
            master = nullptr;
            return true;
        } else {  if master == nullptr -- warrior not hired into an army
            cerr << name << " has no army to run away from!\n";
            return false;
        }
    }
}
