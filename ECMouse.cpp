//
//  ECMouse.cpp
//  
//

#include "ECMouse.h"

ECMouse::ECMouse(std::string name, ECOrganism* prey) {

    _name = name;
    _class = "mouse";
    
    _maxMeals = 10;
    _numMeals = 0;

    _prey = prey;

    _work1Cost = -20;
    _work1 = " is attacking a ";

    _sleepStart = 10;
    _sleepEnd = 18;

}

pair<bool,double> ECMouse::ShouldAttack() {

    // Dead prey or no prey
    if (GetPrey() == NULL) {
        return make_pair(false, 0);
    }

    ECGrasshopper *prey = dynamic_cast<ECGrasshopper*>(GetPrey());
    if (prey == NULL) {
        return make_pair(false, 1);
    }
    return make_pair(true,100);

}
