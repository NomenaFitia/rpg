#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "adventurer.h"
#include "enemy.h"

class CombatSystem {
public:
    CombatSystem(Adventurer* adventurer, Enemy* enemy);
    void startCombat();

private:
    Adventurer* adventurer;
    Enemy* enemy;
};

#endif
