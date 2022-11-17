//
//  ECPanda.cpp
//  
//

#include "ECPanda.h"

ECPanda::ECPanda(std::string name, ECOrganism* prey) {

    _name = name;
    _class = "panda";

    _maxMeals = 12;
    _numMeals = 0;

    _prey = prey;

    _work1Cost = 0;
    _work1 = "";

}

bool ECPanda::IsSleeping(double hour) {
    if (hour >= 15 && hour <= 24) {
        return true;
    }
    if (hour <= 10 && hour >= 0) {
        return true;
    }
    return false;
}

pair<bool,double> ECPanda::ShouldAttack() {
    return make_pair(false, 0);
}
