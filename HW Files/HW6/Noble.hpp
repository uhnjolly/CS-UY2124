//
//  Noble.hpp
//  hw06
//
//  Created by Anjali James on 10/26/19.
//  Copyright © 2019 Anjali James. All rights reserved.
//

#ifndef Noble_hpp
#define Noble_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>


namespace WarriorCraft {
    
    class Warrior;
    
    class Noble {
        
        friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
        
    public:
        Noble(const std::string& name);
        const std::string getName() const;
        bool hire(Warrior& warrior);
        bool fire(Warrior& warrior);
        void modifyStrength(std::vector<Warrior*>& warriors, double ratio);
        void battle(Noble& targetNoble);
        bool removeWarrior(Warrior* targetWarrior);
        
    private:
        std::string name;
        std::vector <Warrior*> warriorArmy;
        double armyStrength = 0;
        bool isAlive = true;
        size_t findWarrior(Warrior* warrior);
    };
    
}
