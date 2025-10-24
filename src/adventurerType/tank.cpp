#include "tank.h"
#include "src/vector2.h"
#include <iostream>

Tank::Tank(Vector2 position) : Adventurer(position, 200, 3) {
    this->armor = 1;
}

int Tank::getArmor() {
    return armor;
}

void Tank::levelUp() {
    level++;
    health += 50 * level;

    armor += 2 + level;
    experience -= EXPERIENCE_MAX;

    std::cout << "Tank Level up to level" << level << "\n";
}

void Tank::takeDamage(int amount)
{
    health -= (amount - armor);
    if (health <= 0) health = 0;
}

