//
//  ECSpider.h
//  
//
#ifndef ECSpider_h
#define ECSpider_h
#include "ECOrganism.h"

class ECSpider : public ECAnthropod {
    public :
        ECSpider(std::string name, ECOrganism* prey = NULL);
        pair<bool, double> ShouldAttack();

    private:
};

#endif /* ECSpider_h */
