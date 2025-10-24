#include "enemy.h"

Enemy::Enemy(std::string type, Vector2 position, int health, int damage, int experience) : Personage(position, health, damage), type(type), experience(experience) {}

char Enemy::getSymbol() const
{
    return symbol;
}

std::string Enemy::getType() const
{
    return type;
}

int Enemy::getExperience()
{
    return experience;
}
