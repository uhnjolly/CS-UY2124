//
//  Warrior.hpp
//  hw06
//
//  Created by Anjali James on 10/26/19.
//  Copyright © 2019 Anjali James. All rights reserved.
//

#ifndef Warrior_hpp
#define Warrior_hpp

#include <stdio.h>

#endif /* Warrior_hpp */
#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Noble;
    
    class Warrior {
    public:
        Warrior(const std::string& name, double warriorStrength);
        
        void modifyStrength(double ratio);
        void display() const;
        const Noble* getOwner() const;
        
        // points to the noble that hired the warrior
        void assignOwner(Noble* noblePtr);
        const std::string getName() const;
        const int getStrength() const;
        bool runaway();
        
    private:
        std::string name;
        double strength;
        Noble* owner = nullptr;
        
    };
}

#endif
