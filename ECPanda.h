//
//  ECPanda.hpp
//  
//

#ifndef ECPanda_h
#define ECPanda_h
#include "ECOrganism.h"

class ECPanda : public ECMammal {
    public :
        ECPanda(std::string name, ECOrganism* prey = NULL);

        pair<bool, double> ShouldAttack() override;

        bool IsSleeping(double hour) override;
};


#endif /* ECPanda_h */
