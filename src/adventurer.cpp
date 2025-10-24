#include "Adventurer.h"
#include "Personage.h"
#include<iostream>

Adventurer::Adventurer(Vector2 position, int health, int damage)
    : Personage(position, health, damage), level(1), experience(0) {}

int Adventurer::getLevel() const {
    return level;
}

int Adventurer::getExperience() const {
    return experience;
}

void Adventurer::gainExperience(int amount)
{
    experience += amount;
    if (experience >= EXPERIENCE_MAX) levelUp();
}

char Adventurer::getSymbol() const
{
    return symbol;
}

void Adventurer::levelUp()
{
    level++;
    health += LIFE_GAIN_PER_EXPERIENCE;

    damage += 1;
    experience -= EXPERIENCE_MAX;

    std::cout << "Player Level up to level" << level << "\n";
}
