//
//  ECOrganism.h
//  
//

#ifndef ECOrganism_h
#define ECOrganism_h

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class ECOrganism
{
public:

    ECOrganism() {};

    virtual pair<bool, double> ShouldAttack() = 0;
    virtual bool IsSleeping(double hour);

    int Work(int type);
    int Eat();
    int Attack();
    
    int GetID() { return _id; }
    double GetHealth() { return _health; }
    string GetName() { return _name; }
    string GetClass() { return _class; }
    ECOrganism* GetPrey() { return _prey; }

    void SetHealth(double h) { _health += h; }
    void SetID(int i) { _id = i; }
    void SetPrey(ECOrganism* p) { _prey = p; }

protected:

  std::string _name;
  std::string _class;
  std::string _work0;
  std::string _work1;

  double _sleepStart;
  double _sleepEnd;

  int _numMeals;
  int _maxMeals;
  int _mealHealth;
  int _work0Cost;
  int _work1Cost;
  
  ECOrganism* _prey;
  
private:

  int _id;
  double _health = 100.0;
  int NotHunting(double preyStatus);
  int HandleAttack(double preyDamage, ECOrganism* prey);

};

class ECAnthropod : public ECOrganism {
  
  public:
    
    ECAnthropod() {
      _sleepStart = 9;
      _sleepEnd = 17;
    }
    
    virtual pair<bool, double> ShouldAttack() = 0;

};

class ECMammal : public ECOrganism {
  
  public :
    ECMammal() {
      _mealHealth = 50;
      _work0Cost = -10;
      _work0 = " ran.";
    }
    virtual pair<bool, double> ShouldAttack() = 0;


};

#endif /* ECOrganism_h */
