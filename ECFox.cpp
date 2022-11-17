//
//  ECFox.cpp
//  
//

#include "ECFox.h"
#include "ECMouse.h"

/*
Limit of eat: 8 times.
2. Sleep: from 7 to 14 hours of the day.
3. Work: (type 1): catch a prey. Fox is only interested in mouse. For other organism, it has no
appetite at all. The prey will be passed in constructor, and won’t change. If a NULL pointer
is passed, then it is not hunting. Cost: 40 vitality.
*/

ECFox::ECFox(std::string name, ECOrganism *prey) {

    _name = name;
    _class = "fox";

    _maxMeals = 8;
    _numMeals = 0;

    _prey = prey;

    _work1Cost = -40;
    _work1 = " is attacking a ";

    _sleepStart = 7;
    _sleepEnd = 14;

}

pair<bool,double> ECFox::ShouldAttack() {
    // Dead prey or no prey
    if (GetPrey() == NULL) {
        return make_pair(false, 0);
    }

    ECMouse *prey = dynamic_cast<ECMouse*>(GetPrey());
    if (prey == NULL) {
        return make_pair(false, 1);
    }
    return make_pair(true, 100);
}
