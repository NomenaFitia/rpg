#include "src/entity.h"
#include "src/vector2.h"

Entity::Entity(Vector2 position) : position(position){}

Vector2 Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const Vector2 &position) {
    this->position = position;
}
