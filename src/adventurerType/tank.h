#ifndef TANK_H
#define TANK_H

#include "src/Adventurer.h"
#include <string>

class Tank : public Adventurer
{
public:
    Tank(Vector2 position);

    int getArmor();
    void levelUp();
    void takeDamage(int amount);

    std::string getType() const { return "tank"; }

private:
    int armor;

};

#endif
