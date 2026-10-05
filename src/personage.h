#ifndef PERSONAGE_H
#define PERSONAGE_H

#include "entity.h"
#include <memory>
#include <vector>

class Personage : public Entity {
protected:

    int health;
    int damage;

public:
    Personage(Vector2 position, int health, int damage);
    virtual ~Personage() = default;

    virtual void takeDamage(int amount);
    virtual void attack(Personage* target);
    virtual void move(const Vector2 direction);

    int getDamage() const;
    int getHealth() const;
    bool isAlive() const;

    static Vector2 choisirDirectionAleatoire();
    std::vector<Entity*> findNeighbors(const Entity &entity, const std::vector<std::unique_ptr<Entity>> &allEntities, int range);

    Vector2 position;

};

#endif
