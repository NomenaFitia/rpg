#ifndef ENEMY_H
#define ENEMY_H

#include "Personage.h"
#include <string>


class Enemy : public Personage
{
protected:
    char symbol = 'E';
    std::string type;
    int experience;

public:
    Enemy(std::string type,Vector2 position, int health, int damage, int experience);
    char getSymbol() const;
    std::string getType() const;
    int getExperience();
};

#endif
