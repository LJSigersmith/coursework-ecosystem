//
//  ECCaterpillar.cpp
//  
//
#include "ECCaterpillar.h"

ECCaterpillar::ECCaterpillar(std::string name) {

    _name = name;
    _class = "caterpillar";

    _maxMeals = 5;
    _numMeals = 0;
    _mealHealth = 15;

    _prey = NULL;

    _work0Cost = -10;
    _work1Cost = 0;
    _work0 = " climbed a tree.";
    _work1 = "";

}
