//
//  ECOrganism.cpp
//  
//

#include "ECOrganism.h"

bool ECOrganism::IsSleeping(double hour) {
      if (hour <= _sleepEnd && hour >= _sleepStart) {
        return true;
      }
      return false;
}

int ECOrganism::Eat() {
  if (_health == 0) { cout << _name << "can't eat. He's dead now."; return 5; }
      if (_numMeals == _maxMeals) { cout << _name << " can't eat. He's already eaten his max number of meals."; return 0; }

      _numMeals++;
      string modifier;

      if (_health + _mealHealth <= 100) {
          _health += _mealHealth;
          modifier = "now";
      } else if (_health < 100) {
          modifier = "now";
          _health = 100;
      } else {
          modifier = "still";
      }
      
      cout << _name << " ate. His health is " << modifier << " at: " << _health << "%" << endl;
      return 0;
}

int ECOrganism::Work(int type) {
  if (type == 0) {
        SetHealth(_work0Cost);
        cout << GetName() << _work0 << " His health is now at: " << GetHealth() << "%" << endl;
        if (GetHealth() <= 0) { return -5; }
      }
      if (type == 1) {
        return Attack();
      }

      return 0;
}

int ECOrganism::NotHunting(double preyStatus) {
  // Prey doesnt exist, no vitality cost
  if (preyStatus == 0) {
    cout << GetName() << " is not hunting. Health is still at " << GetHealth() << "%" << endl;
    return 0;
  }
  // Incorrect prey type, still costs vitality
  if (preyStatus == 1) {
    SetHealth(_work1Cost);
    cout << GetName() << " is not interested in hunting " << GetPrey()->GetName() << "." << endl;
    
    // Organism died after hunting wrong prey type
    if (GetHealth() <= 0) {
      cout << GetName() << " died trying to hunt." << endl;
      return -5;
    } else {
        cout << "Health is now at " << GetHealth() << "%" << endl;
        return 0;
    }
  }
  return 0;
}

int ECOrganism::HandleAttack(double preyDamage, ECOrganism* prey) {
// 4 Attack Outcomes:
// Prey Damage is 100, and Killed Itself (Kill Prey and Itself) (-1)
// Prey Damage is 100, and Still Alive   (Kill Prey) (-2)
// Prey Damage is x, and Killed Itself   (Kill Itself and Modify Prey Health) (-5)
// Prey Damage is x, and Still Alive     (Modify Prey Health) (0)

  if (preyDamage == 100 && GetHealth() <= 0) {
      cout << GetName() << " killed " << prey->GetName() << " and died in the process" << endl;
      return -1;
  }
  if (preyDamage == 100 && GetHealth() > 0) {
      cout << GetName() << " killed " << prey->GetName() << ". Health is now at: " << GetHealth() << "%" << endl;
      return -2;
  }
  if (preyDamage != 100 && GetHealth() <= 0) {
      cout << GetName() << " attacked " << prey->GetName() << " for " << preyDamage << " damage, and died in the process. " << endl;
      prey->SetHealth(preyDamage);
      // Did the attack kill the prey?
      if (prey->GetHealth() <= 0) {
        cout << "This attack killed " << prey->GetName() << endl;
        return -1; // Then kill prey and itself
      } else {
        cout << prey->GetName() << "'s health is now at: " << prey->GetHealth() << "%" << endl;
        return -5; // Then kill itself
      }
  }
  if (preyDamage != 100 && GetHealth() > 0) {
      cout << GetName() << " attacked " << prey->GetName() << " for " << preyDamage << " damage. Health is now at: " << GetHealth() << "%" << endl;
      prey->SetHealth(preyDamage);
      // Did the attack kill the prey?
      if (prey->GetHealth() <= 0) {
        cout << "This attack killed " << prey->GetName() << endl;
        return -2; // Then kill prey
      } else {
        cout << prey->GetName() << "'s health is now at: " << prey->GetHealth() << "%" << endl;
        return 0;
      }
      
  }
  return 0;
}

int ECOrganism::Attack() {

      pair<bool, double> attackResult = ShouldAttack();
      bool shouldAttack = attackResult.first;
      double preyDamage = attackResult.second;

      if(!shouldAttack) { return NotHunting(attackResult.second); }

      ECOrganism *prey = GetPrey();
      cout << GetName() << _work1 << prey->GetClass() << ", " << prey->GetName() << endl;
      SetHealth(_work1Cost);

      return HandleAttack(preyDamage, prey);
}
