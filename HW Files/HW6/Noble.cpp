//
//  Noble.cpp
//  hw06
//
//  Created by Anjali James on 10/26/19.
//  Copyright © 2019 Anjali James. All rights reserved.
//

#include "Noble.hpp"
#include "Warrior.hpp"

using namespace std;

namespace WarriorCraft {
    ostream& operator<<(ostream& os, const Noble& rhs) {
        os << rhs.name << " has an army of " << rhs.warriorArmy.size() << endl;
        for (size_t i = 0; i < rhs.warriorArmy.size(); ++i) {
            rhs.warriorArmy[i]->display();
        }
        return os;
    }
    
    Noble::Noble(const string& name) : name(name) {}
    
    const string Noble::getName() const { return name; }
    
    bool Noble::hire(Warrior& warrior) {
        // first checks if noble is able to hire
        if (!isAlive) {
            cerr << "Can't hire if you're dead!\n";
            return false;
        }
        
        // if the warrior has not been hired yet
        if (warrior.getOwner() != nullptr) {
            cerr << warrior.getName() << " has an owner already.\n";
            return false;
        } else { // warrior's owner is the one calling hire function
            warrior.assignOwner(this);
            warriorArmy.push_back(&warrior);
            armyStrength += warrior.getStrength();
            return true;
        }
    }
    
    bool Noble::fire(Warrior& warrior) {
        cout << warrior.getName() << ", you're fired! -- " << name << endl;
        
        size_t index = findWarrior(&warrior);
        
        // removes warrior from vector while maintaining the order
        if (index != warriorArmy.size()) {
            for (size_t i = index; i < warriorArmy.size(); ++i) {
                warriorArmy[i] = warriorArmy[i+1];
            }
            warriorArmy.pop_back();
            warrior.assignOwner(nullptr);           // warrior no longer has an owner to point to
            armyStrength -= warrior.getStrength();  // updating army strength
            return true;
        } else {
            cerr << warrior.getName() << " is not in the army.\n";
            return false;
        }
        
    }
    
    // updates each warrior's strength by the ratio
    void Noble::modifyStrength(vector<Warrior*>& warriors, double ratio) {
        for (size_t i = 0; i < warriors.size(); ++i) {
            warriors[i]->modifyStrength(ratio);
        }
    }
    
    
    void Noble::battle(Noble& targetNoble) {
        //        cout << name << " " << armyStrength << endl;
        //        cout << targetNoble.name << " " << targetNoble.armyStrength << endl;
        
        cout << name << " battles " << targetNoble.name << endl;
        
        if (!isAlive && !targetNoble.isAlive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!isAlive && targetNoble.isAlive) {
            cout << "He's dead, " << targetNoble.name << endl;
        } else if (isAlive && !targetNoble.isAlive) {
            cout << "He's dead, " << name << endl;
        } else { //if they're both alive
            if (armyStrength == targetNoble.armyStrength) {
                cout << "Mutual Annihilation: " << name << " and " << targetNoble.name << " die at each other's hands." << endl;
                
                //updating strength of warriors within vectors
                modifyStrength(warriorArmy, 0);
                targetNoble.modifyStrength(targetNoble.warriorArmy, 0);
                
                // because they both kill each other, both army strengths get set to 0
                armyStrength = 0;
                targetNoble.armyStrength = 0;
                isAlive = false;
                targetNoble.isAlive = false;
                
                // if this army is stronger than the target
            } else if (armyStrength > targetNoble.armyStrength) {
                cout << name << " defeats " << targetNoble.name << endl;
                
                double battleRatio = targetNoble.armyStrength / armyStrength;
                
                //updating strength of warriors within vectors
                modifyStrength(warriorArmy, battleRatio);
                targetNoble.modifyStrength(targetNoble.warriorArmy, battleRatio);
                
                armyStrength -= armyStrength * battleRatio;
                targetNoble.armyStrength = 0;
                targetNoble.isAlive = false;
                
            } else { // (armyStrength < targetNoble.armyStrength)
                cout << targetNoble.name << " defeats " << name << endl;
                
                double battleRatio = armyStrength / targetNoble.armyStrength;
                
                //updating strength of warriors within vectors
                modifyStrength(warriorArmy, battleRatio);
                targetNoble.modifyStrength(targetNoble.warriorArmy, battleRatio);
                
                targetNoble.armyStrength -= targetNoble.armyStrength * battleRatio;
                armyStrength = 0;
                isAlive = false;
            }
        }
    }
    
    // removes warrior from vector if they runaway
    bool Noble::removeWarrior(Warrior* targetWarrior) {
        size_t index = findWarrior(targetWarrior);
        
        if (index != warriorArmy.size()) {
            for (size_t i = index; i < warriorArmy.size(); ++i) {
                warriorArmy[i] = warriorArmy[i+1];
            }
            warriorArmy.pop_back();
            // updating strength of army
            armyStrength -= targetWarrior->getStrength();
            return true;
        } else {
            cerr << targetWarrior->getName() << " is not in the army.\n";
            return false;
        }
    }
    
    // returns index of warrior if he's in the army
    // if not, returns size of army
    size_t Noble::findWarrior(Warrior* warrior) {
        for (size_t i = 0; i < warriorArmy.size(); ++i) {
            if (warriorArmy[i] == warrior) {
                return i;
            }
        }
        return warriorArmy.size();
    }
}
