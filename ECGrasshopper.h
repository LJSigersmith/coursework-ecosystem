//
//  ECGrasshopper.h
//  
//
#ifndef ECGrasshopper_h
#define ECGrasshopper_h
#include "ECOrganism.h"

class ECGrasshopper : public ECAnthropod {
    public :
        ECGrasshopper(std::string name, ECOrganism* prey = NULL);
        
        //int Work(int type);
        std::pair<bool,double> ShouldAttack();

    private:
};

#endif /* ECGrasshopper_h */
