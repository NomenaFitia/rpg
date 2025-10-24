#include "assassin.h"
#include "src/vector2.h"
#include <iostream>

Assassin::Assassin(Vector2 position) :  Adventurer(position, 100, 10){}

void Assassin::levelUp()
{
    level++;
    health += 50;

    damage += 5 * level;
    experience -= EXPERIENCE_MAX;

    std::cout << "Assassin Level up to level" << level << "\n";
}

void Assassin::takeDamage(int amount)
{
    int chance = random();
    if (chance < 8) Personage::takeDamage(amount);
}

void Assassin::attack(Personage *personage)
{
    int chance = random();

    if (chance < 8)
    {
        personage->takeDamage(damage * 2);
    }

    else {
        personage->takeDamage(damage);
    }


}

int Assassin::random()
{
    return rand() % 10;
}

