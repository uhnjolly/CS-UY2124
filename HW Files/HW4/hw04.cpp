
//  hw04.cpp
//  hw04
//
//  Created by Anjali James on 10/3/19.
//  Copyright © 2019 Anjali James. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;


class Noble;

class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength << endl;
        return os;
    }
    
public:
    Warrior(const string& name, double strength) : name(name), strength(strength) {}
    
    string getName() const { return name; }
    
    int getStrength() const { return strength; }
    
    Noble* getMaster() const { return owner; }
    
    void assignOwner(Noble* noble) {
        owner = noble;
    }
    
    //set strength
    void ChangeStrength(double RatioOfBattle) {
        if (RatioOfBattle == 0) {
            strength = 0;
        } else {
            strength -= (strength * RatioOfBattle);
        }
    }
    
    
private:
    const string name;
    double strength;
    Noble* owner = nullptr;
    //    bool isHired = false;
    
};

class Noble {
    friend ostream& operator<<(ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.warriorArmy.size() << endl;
        for (size_t i = 0; i < noble.warriorArmy.size(); ++i) {
            os << "     " << noble.warriorArmy[i]->getName() << ": " << noble.warriorArmy[i]->getStrength() << endl;
        }
        return os;
    }
    
public:
    Noble(const string& name) : name(name) {}
    
    
    bool hire(Warrior& warrior) {
        if (!isAlive) { return false; }
        
        if (warrior.getMaster() == nullptr) { // if the warrior was not hired yet
            warriorArmy.push_back(&warrior);
            armyStrength += warrior.getStrength();  // adds warrior strength to army strength
            warrior.assignOwner(this);
            return true;
        } else {
            return false;
        }
    }
    
     Warrior* fire(const string& warriorName) {
     cout << "You don't work for me anymore, " << warriorName << "! -- " << name;
     
     size_t lastInd = warriorArmy.size() - 1;
     
     if (isAlive) {
     for (size_t i = 0; i < warriorArmy.size(); ++i) {           // if the noble is alive and the warrior is in the army
     if (warriorArmy[i]->getName() == warriorName) {
     armyStrength -= warriorArmy[i]->getStrength();      // updating strength
     //                    warriorArmy[i]->changeHired();                      // updating hired status of target warrior
     size_t tempInd = i;
     warriorArmy[i]->assignOwner(nullptr);
     warriorArmy[i] = warriorArmy[lastInd];
     warriorArmy[lastInd] = warriorArmy[tempInd];        // then we move the desired warrior to the back of the vector
     Warrior* firedWarrior = warriorArmy[lastInd];       // create a warrior pointer of the warrior we are firing so we can return it
     warriorArmy.pop_back();                             // removing the fired warrior from the noble's army
     return firedWarrior;
     }
     }
     return nullptr;
     }
     return nullptr;
     }
     */
    
    
    bool fire(const string& warriorName) {
        cout << "You don't work for me anymore, " << warriorName << "! -- " << name << ".";
        
        size_t lastInd = warriorArmy.size() - 1;
        
        if (isAlive) {
            for (size_t i = 0; i < warriorArmy.size(); ++i) {           // if the noble is alive and the warrior is in the army
                if (warriorArmy[i]->getName() == warriorName) {
                    armyStrength -= warriorArmy[i]->getStrength();      // updating strength
                    warriorArmy[i]->assignOwner(nullptr);               // setting owner of warrior to no one
                    size_t tempInd = i;
                    warriorArmy[i] = warriorArmy[lastInd];
                    warriorArmy[lastInd] = warriorArmy[tempInd];        // then we move the desired warrior to the back of the vector
                    warriorArmy.pop_back();                             // removing the fired warrior from the noble's army
                    return true;
                }
            }
            return false;
        }
        return false;
    }
    
    
    void battle(Noble& targetNoble) {
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
                for (size_t i = 0; i < warriorArmy.size(); ++i) {
                    warriorArmy[i]->ChangeStrength(0);
                }
                
                for (size_t k = 0; k < targetNoble.warriorArmy.size(); ++k) {
                    targetNoble.warriorArmy[k]->ChangeStrength(0);
                }
                armyStrength = 0;
                targetNoble.armyStrength = 0;
                isAlive = false;
                targetNoble.isAlive = false;
            } else if (armyStrength > targetNoble.armyStrength) {
                cout << name << " defeats " << targetNoble.name << endl;
                
                double RatioOfBattle = targetNoble.armyStrength / armyStrength;
                
                for (size_t i = 0; i < warriorArmy.size(); ++i) {
                    warriorArmy[i]->ChangeStrength(RatioOfBattle);
                }
                for (size_t k = 0; k < targetNoble.warriorArmy.size(); ++k) {
                    targetNoble.warriorArmy[k]->ChangeStrength(0);
                }
                
                armyStrength -= armyStrength*RatioOfBattle;
                //                cout << "ArmyA strength is now: " << armyStrength << endl;;
                targetNoble.armyStrength = 0;
                targetNoble.isAlive = false;
                
            } else { // (armyStrength < targetNoble.armyStrength)
                cout << targetNoble.name << " defeats " << name << endl;
                
                double RatioOfBattle = armyStrength/targetNoble.armyStrength;
                
                for (size_t i = 0; i < warriorArmy.size(); ++i) {
                    warriorArmy[i]->ChangeStrength(0);
                }
                for (size_t k = 0; k < targetNoble.warriorArmy.size(); ++k) {
                    targetNoble.warriorArmy[k]->ChangeStrength(RatioOfBattle);
                }
                targetNoble.armyStrength -= targetNoble.armyStrength*RatioOfBattle;
                //                cout << "ArmyB strength is now: " << armyStrength << endl;
                
                armyStrength = 0;
                isAlive = false;
            }
        }
    }
    
    string getName() const { return name; }
    
    // loops through the army to see if a warrior is in it
    bool InArmy(const string& warriorName) {
        for (size_t i = 0; i < warriorArmy.size(); ++i) {
            if (warriorArmy[i]->getName() == warriorName) {
                return true;
            }
        }
        return false;
    }
    void clearArmy() {
        for (size_t i = 0; i < warriorArmy.size(); ++i) {
            delete warriorArmy[i];
            warriorArmy[i] = nullptr;
        }
        warriorArmy.clear();
    }
private:
    const string name;
    vector<Warrior*> warriorArmy;
    double armyStrength = 0;
    bool isAlive = true;
    
};

// checks if the desired noble is in the vector
bool nobleExists(const vector<Noble*>& nobleVec, const string& nobleName) {
    for (size_t i = 0; i < nobleVec.size(); ++i) {
        if (nobleVec[i]->getName() == nobleName) {
            return true;
        }
    }
    return false;
}

void addNewNoble(vector<Noble*>& nobleVec, const string& nobleName) {
    if (!nobleExists(nobleVec, nobleName)) {                         // checks if the noble already exists in the noble vector
        nobleVec.push_back(new Noble(nobleName));                       // if not, noble will be pushed to vector and allocated on the heap
    } else {
        cout << nobleName << " already exists!" << endl;
    }
}

// checks if the desired warrior is in the vector
bool warriorExists(const vector<Warrior*>& warriorVec,
                   const vector<Noble*>& nobleVec,
                   const string& warriorName) {
    for (size_t i = 0; i < warriorVec.size(); ++i) {            // we want to check if the warrior exists in the warrior vector
        if (warriorVec[i]->getName() == warriorName) {
            return true;
        }
    }
    
    for (size_t i = 0; i < nobleVec.size(); ++i) {                   // we then check if the warrior is in the army of one of the nobles
        if (nobleVec[i]->InArmy(warriorName)) {               // when firing a warrior, we want to check if that warrior is in the army
            return true;
        }
    }
    return false;
}

// creates a warrior on the heap if it didn't exist yet
void addNewWarrior(vector<Warrior*>& warriorVec,
                   vector<Noble*>& nobleVec,
                   const string& warriorName,
                   int strength) {
    if (!warriorExists(warriorVec, nobleVec, warriorName)) {         // checks if the specified warrior exists
        warriorVec.push_back(new Warrior(warriorName, strength));    // if not, it will add the warrior to the warriors vector
    } else {
        cout << warriorName << " already exists!" << endl;
    }
}

bool hireCommand(vector<Warrior*>& warriorVec,
                 vector<Noble*>& nobleVec,
                 const string warriorName,
                 const string nobleName) {
    
    //    size_t lastInd = warriorVec.size() - 1;
    
    for (size_t i = 0; i < nobleVec.size(); ++i) {
        if (nobleVec[i]->getName() == nobleName) {
            for (size_t k = 0; k < warriorVec.size(); ++k) {
                if (warriorVec[k]->getName() == warriorName) {
                    if (nobleVec[i]->hire(*warriorVec[k])) {
                        return true;
                        break;
                    } else {
                        cout << nobleName << " is dead! You can't hire someone if you're dead." << endl;
                        return false;
                    }
                }
            }
            // the desired warrior can't be hired because it's in someone else's army or doesn't exist
            cout << warriorName << " either does not exist or is already hired!" << endl;
            return false;
        }
    }
    // desired noble doesn't exist
    cout << nobleName << " doesn't exist." << endl;
    return false;
}

/* This code was written with the intent that there was a vector for unemployed warriors only --  FOR hireCommand
 cout << warriorName << " gets hired by " << nobleName << endl;
 size_t targetWarriorInd = k;
 warriorVec[k] = warriorVec[lastInd];
 warriorVec[lastInd] = warriorVec[targetWarriorInd];
 warriorVec.pop_back();
 */


bool fireCommand(vector<Noble*>& nobleVec,
                 vector<Warrior*>& warriorVec,
                 const string& nobleName,
                 const string& warriorName) {
    if (nobleExists(nobleVec, nobleName)) {                         // checks if noble exists first
        for (size_t i = 0; i < nobleVec.size(); ++i) {
            if (nobleVec[i]->getName() == nobleName) {              // finds the noble specified
                if (nobleVec[i]->InArmy(warriorName)) {      // then checks if the warrior is in the army to fire
                    nobleVec[i]->fire(warriorName);                 // if it is, they will be fired
                    return true;
                    break;
                }
                cout << warriorName << " is not in the army!" << endl;  // warrior specified isn't in the noble's army
                return false;
            }
        }
    }
    cout << nobleName << " does not exist." << endl;                // noble doesn't exist
    return false;
}

* -- This code was written with the intent that there was a vector for unemployed warriors only -- FOR fireCommand
 if (nobleExists(nobleVec, nobleName)) {
 for (size_t i = 0; i < nobleVec.size(); ++i) {
 if (nobleVec[i]->InArmy(warriorName)) {
 nobleVec[i]->fire(warriorName);
 break;
 }
 }
 }
 if (!nobleExists(nobleVec, nobleName)) {
 cout << nobleName << " does not exist." << endl;
 return false;
 }
 cout << warriorName << " is not in " << nobleName << "'s army!" << endl;
 return false;
 }
 */

void displayNobles(const vector<Noble*>& nobles) {
    cout << "Nobles:" << endl;
    
    if (nobles.size() == 0) {
        cout << "NONE" << endl;
    }
    
    for (size_t i = 0; i < nobles.size(); ++i) {
        cout << *nobles[i] << endl;
    }
}

void displayWarriors(const vector<Warrior*>& warriors) {
    cout << "Unemployed Warriors: " << endl;
    
    size_t unemployedCounter = 0;                       // keep a count of how many unemployed warriors in vector
    
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i]->getMaster() == nullptr) {
            ++unemployedCounter;                        // increment count for each unemployed warrior in vector
            cout << *(warriors[i]) << endl;
        }
    }
    
    if (unemployedCounter == 0) {                       // if there are no unemployed warriors, display NONE
        cout << "NONE" << endl;
    }
    
}
/* This code was written with the intent that there was a vector for unemployed warriors only -- FOR displayWarriors
 if (warriors.size() == 0) {
 cout << "NONE" << endl;
 }
 
 for (size_t i = 0; i < warriors.size(); ++i) {
 cout << *warriors[i] << endl;
 }
 }
 */


void battle(vector<Noble*>& nobles, const string& nobleA, const string& nobleB) {
    if (nobleExists(nobles, nobleA) && nobleExists(nobles, nobleB)) {
        for (size_t i = 0; i < nobles.size(); ++i) {
            if (nobles[i]->getName() == nobleA) {
                for (size_t j = 0; j < nobles.size(); ++j) {
                    if (nobles[j]->getName() == nobleB) {
                        nobles[i]->battle(*nobles[j]);
                        break;
                    }
                }
            }
        }
    } else if (!nobleExists(nobles, nobleA) && nobleExists(nobles, nobleB)) {
        cout << nobleA << " does not exist!" << endl;
    } else { //nobleExists(nobles, nobleA) && !nobleExists(nobles, nobleB)
        cout << nobleB << " does not exist!" << endl;
    }
}

// deletes the nobles off the heap
void clearCommand(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    //    cout << "clearing nobles & warriors..." << endl;
    for (size_t i = 0; i < nobles.size(); ++i) {
        nobles[i]->clearArmy();                         // first deletes warriors in the army of each noble
        delete nobles[i];                               // then deletes each noble
        nobles[i] = nullptr;                            // noble pointer no longer validly points to anything
    }
    
    nobles.clear();                                     // emptying the vectors out
    warriors.clear();
}

int main() {
    ifstream inputFile("nobleWarriors.txt");
    if (!inputFile) {
        cerr << "Failed to open file.";
        exit(1);
    }
    
    string command, nobleNameA, nobleNameB, warriorName;
    double strength;
    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    
    while (inputFile >> command) {
        if (command == "Noble") {
            inputFile >> nobleNameA;
            if (!nobleExists(nobles, nobleNameA)) {
                addNewNoble(nobles, nobleNameA);
            }
        } else if (command == "Warrior") {
            inputFile >> warriorName >> strength;
            if (!warriorExists(warriors, nobles, warriorName)) {
                addNewWarrior(warriors, nobles, warriorName, strength);
            }
        } else if (command == "Hire") {
            inputFile >> nobleNameA >> warriorName;
            hireCommand(warriors, nobles, warriorName, nobleNameA);
        } else if (command == "Status") {
            cout << "Status\n" << "======" << endl;
            displayNobles(nobles);
            displayWarriors(warriors);
        } else if (command == "Fire") {
            inputFile >> nobleNameA >> warriorName;
            fireCommand(nobles, warriors, nobleNameA, warriorName);
            cout << endl;
        } else if (command == "Battle") {
            inputFile >> nobleNameA >> nobleNameB;
            battle(<#int &nobles#>, <#const string &nobleA#>, <#const string &nobleB#>)(nobles, nobleNameA, nobleNameB);
        } else { // command == "Clear"
            clearCommand(nobles, warriors);
        }
    }
    //    cout << "Nobles: " << nobles.size() << endl;
    //    cout << "Warriors: " << warriors.size() << endl;
    inputFile.close();
}
