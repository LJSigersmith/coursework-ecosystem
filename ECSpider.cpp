//
//  ECSpider.cpp
//  
//

#include "ECSpider.h"

ECSpider::ECSpider(std::string name, ECOrganism* prey) {

    _name = name;
    _class = "spider";

    _maxMeals = 5;
    _numMeals = 0;
    _mealHealth = 20;

    _prey = prey;

    _work0Cost = -10;
    _work1Cost = -30;
    _work0 = " weaved a web.";
    _work1 = "is attacking a ";

}

pair<bool, double> ECSpider::ShouldAttack() {
    
    // Dead prey or no prey
    if (GetPrey() == NULL) {
        return make_pair(false, 0);
    }

    ECAnthropod* prey = dynamic_cast<ECAnthropod*>(GetPrey());
    if (prey == NULL) {
        return make_pair(false,1);
    }
    return make_pair(true,100);
}