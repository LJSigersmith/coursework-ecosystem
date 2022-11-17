//
//  ECFox.h
//  
//

#ifndef ECFox_h
#define ECFox_h
#include "ECOrganism.h"

class ECFox : public ECMammal {
    public :
        ECFox(std::string name, ECOrganism* prey = NULL);

        pair<bool, double> ShouldAttack();
};

#endif /* ECFox_h */
