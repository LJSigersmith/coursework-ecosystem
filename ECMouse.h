//
//  ECMouse.h
//  
//

#ifndef ECMouse_h
#define ECMouse_h
#include "ECOrganism.h"
#include "ECGrasshopper.h"

class ECMouse : public ECMammal {
    public :
        ECMouse(std::string name, ECOrganism* prey = NULL);

        pair<bool,double> ShouldAttack();
};

#endif /* ECMouse_h */
