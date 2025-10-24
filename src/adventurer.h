#ifndef ADVENTURER_H
#define ADVENTURER_H

#include "Personage.h"
#include <string>

class Adventurer : public Personage {
protected:

    char symbol = 'A';
    int level;
    int experience;

public:
    Adventurer(Vector2 position, int health, int damage);
    virtual ~Adventurer() = default;

    virtual void levelUp();
    virtual std::string getType() const { return "Aventurier"; }

    int getLevel() const;
    int getExperience() const;

    virtual void gainExperience(int amount);
    virtual char getSymbol() const;

    static const int EXPERIENCE_MAX = 10;
    static const int LIFE_GAIN_PER_EXPERIENCE = 2;
};

#endif
