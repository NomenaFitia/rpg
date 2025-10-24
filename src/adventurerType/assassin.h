#ifndef ASSASSIN_H
#define ASSASSIN_H

#include <src/Adventurer.h>
#include <string>


class Assassin : public Adventurer
{
public:
    Assassin(Vector2 position);

    void levelUp();
    void takeDamage(int amount);
    void attack(Personage* personage);

    std::string getType() const { return "assassin"; }
    static int random();

private:
};

#endif
