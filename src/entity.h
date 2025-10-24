#ifndef ENTITY_H
#define ENTITY_H

#include "vector2.h"

class Entity {
protected:
    Vector2 position;

public:
    Entity(Vector2 position);
    virtual ~Entity() = default;

    Vector2 getPosition() const;
    void setPosition(const Vector2& position);

    virtual char getSymbol() const = 0;
};

#endif
