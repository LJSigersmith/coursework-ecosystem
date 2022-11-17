//
//  ECCaterpillar.h
//  
//

#ifndef ECCaterpillar_h
#define ECCaterpillar_h
#include "ECOrganism.h"

class ECCaterpillar : public ECAnthropod {
    public :
        ECCaterpillar(std::string name);
        pair<bool, double> ShouldAttack() { return make_pair(false,0); }
};

#endif /* ECCaterpillar_h */
