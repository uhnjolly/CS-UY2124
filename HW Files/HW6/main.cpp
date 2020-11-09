//
//  main.cpp
//  hw06
//
//  Created by Anjali James on 10/26/19.
//  Copyright © 2019 Anjali James. All rights reserved.
//

#include <iostream>
#include "Noble.hpp"
#include "Warrior.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace WarriorCraft;


 class Noble;
 class Warrior {
 public:
 Warrior(const string& name, double warriorStrength) : name(name), strength(warriorStrength) {}
 void modifyStrength(double ratio) {
 strength -= (strength * ratio);
 }
 void display() {
 cout << name << ": " << strength << endl;
 }
 const Noble* getOwner() const { return owner; }
 // points to the noble that hired the warrior
 void assignOwner(Noble* noblePtr) {
 owner = noblePtr;
 }
 const string getName() const { return name; }
 const int getStrength() const { return strength; }
 bool runaway() {
 cout << name << " flees in terror, abandoning his lord, " << owner->getName() << endl;
 if (owner != nullptr) {
 owner->removeWarrior(this);
 owner = nullptr;
 return true;
 } else {
 cerr << name << " has no army to run away from!\n";
 return false;
 }
 }
 private:
 string name;
 double strength;
 Noble* owner = nullptr;
 };
 class Noble {
 friend ostream& operator<<(ostream& os, const Noble& rhs) {
 os << rhs.name << " has an army of " << rhs.warriorArmy.size() << endl;
 for (size_t i = 0; i < rhs.warriorArmy.size(); ++i) {
 rhs.warriorArmy[i]->display();
 }
 return os;
 }
 public:
 Noble(const string& name) : name(name) {}
 const string getName() const { return name; }
 bool hire(Warrior& warrior) {
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
 bool fire(Warrior& warrior) {
 cout << warrior.getName() << ", you're fired! -- " << name << endl;
 size_t warriorInd = findWarrior(&warrior);
 if (warriorInd != warriorArmy.size()) {
 for (size_t i = warriorInd; i < warriorArmy.size(); ++i) {
 warriorArmy[i] = warriorArmy[i+1];
 }
 warriorArmy.pop_back();
 warrior.assignOwner(nullptr);       // warrior no longer has an owner to point to
 armyStrength -= warrior.getStrength();
 return true;
 } else {
 cerr << warrior.getName() << " is not in the army.\n";
 return false;
 }
 }
 void modifyStrength(vector<Warrior*>& warriors, double ratio) {
 for (size_t i = 0; i < warriors.size(); ++i) {
 warriors[i]->modifyStrength(ratio);
 }
 }
 void battle(Noble& targetNoble) {
 //        cout << name << " " << armyStrength << endl;
 //        cout << targetNoble.name << " " << targetNoble.armyStrength << endl;
 cout << name << " battles " << targetNoble.name << endl;
 if (!isAlive && !targetNoble.isAlive) {
 cout << "Oh YUCK! They're both dead!" << endl;
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
 armyStrength *= battleRatio;
 targetNoble.armyStrength = 0;
 targetNoble.isAlive = false;
 } else { // (armyStrength < targetNoble.armyStrength)
 cout << targetNoble.name << " defeats " << name << endl;
 double battleRatio = armyStrength/targetNoble.armyStrength;
 //updating strength of warriors within vectors
 modifyStrength(warriorArmy, battleRatio);
 targetNoble.modifyStrength(targetNoble.warriorArmy, battleRatio);
 targetNoble.armyStrength *= battleRatio;
 armyStrength = 0;
 isAlive = false;
 }
 }
 }
 bool removeWarrior(Warrior* targetWarrior) {
 size_t warriorInd = findWarrior(targetWarrior);
 if (warriorInd != warriorArmy.size()) {
 for (size_t i = warriorInd; i < warriorArmy.size(); ++i) {
 warriorArmy[i] = warriorArmy[i+1];
 }
 warriorArmy.pop_back();
 warriorArmy -= targetWarrior->getStrength();
 return true;
 } else {
 cerr << targetWarrior->getName() << " is not in the army.\n";
 return false;
 }
 }
 private:
 string name;
 vector <Warrior*> warriorArmy;
 double armyStrength = 0;
 bool isAlive = true;
 size_t findWarrior(Warrior* warrior) {
 for (size_t i = 0; i < warriorArmy.size(); ++i) {
 if (warriorArmy[i] == warrior) {
 return i;
 }
 }
 return warriorArmy.size();
 }
 };
 */

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    //
    cheetah.runaway();
    cout << art << endl;
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}
