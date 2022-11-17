//
//  ECGrasshopper.cpp
//  
//

#include "ECGrasshopper.h"
#include "ECSpider.h"
#include "ECMouse.h"

ECGrasshopper::ECGrasshopper(std::string name, ECOrganism* prey) {

    _name = name;
    _class = "grasshopper";

    _maxMeals = 10;
    _numMeals = 0;
    _mealHealth = 25;

    _prey = prey;

    _work0Cost  = -5;
    _work1Cost = -40;
    _work0 = " hopped around.";
    _work1 = " is attacking a ";
}

pair<bool, double> ECGrasshopper::ShouldAttack() {

    // Dead prey or no prey
    if (GetPrey() == NULL) {
        return make_pair(false, 0);
    }

    ECGrasshopper* grasshopper = dynamic_cast<ECGrasshopper*>(GetPrey());
    ECSpider* spider = dynamic_cast<ECSpider*>(GetPrey());
    ECMouse* mouse = dynamic_cast<ECMouse*>(GetPrey());
    
    pair<bool,double> result = make_pair(false, 0);

    if (grasshopper == NULL && spider == NULL && mouse == NULL) {
       return make_pair(false, 1);
    }
    if (mouse != NULL) {
        return make_pair(true, -5);
    }
    return make_pair(true, 100);

}
