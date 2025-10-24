#include "CombatSystem.h"
#include <iostream>

CombatSystem::CombatSystem(Adventurer* adventurer, Enemy* enemy)
    : adventurer(adventurer), enemy(enemy) {}

void CombatSystem::startCombat() {
    while (adventurer->isAlive() && enemy->isAlive()) {
        adventurer->attack(enemy);

        std::cout << "aventurier ---" << adventurer->getDamage() << "--> enemy" << std::endl;

        if (enemy->isAlive()) {
            enemy->attack(adventurer);
            std::cout << "enemy ---" << enemy->getDamage() << "--> aventurier " << std::endl;

        }
    }

    if (!enemy->isAlive()) {
        adventurer->gainExperience(enemy->getExperience());
        std::cout << "Le monstre est mort !" << std::endl;
    } else {
        std::cout << "L'aventurier est mort !" << std::endl;
    }
}
