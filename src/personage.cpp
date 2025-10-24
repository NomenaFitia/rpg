#include "src/Personage.h"
#include <iostream>
#include <ostream>
#include <random>

Personage::Personage(Vector2 position, int health, int damage) : Entity(position), health(health), damage(damage) {}

std::vector<Vector2> directions = {
    {0, -1},         // Nord
    {0, 1},          // Sud
    {-1, 0},         // Ouest
    {1, 0},          // Est
};

void Personage::takeDamage(int amount) {
    health -= amount;
    if (health <= 0) health = 0;
}

int Personage::getHealth() const {
    return health;
}

int Personage::getDamage() const {
    return damage;
}

void Personage::attack(Personage* target)
{
    target->takeDamage(damage);
    std::cout << " combat " << std::endl;
}

void Personage::move(Vector2 direction)
{
    this->setPosition(getPosition() + direction);
}

std::vector<Entity *> Personage::findNeighbors(const Entity &entity, const std::vector<std::unique_ptr<Entity>> &allEntities, int range)
{
    std::vector<Entity*> neighbors;

    for (const auto& e : allEntities) {
        if (e.get() != &entity && entity.getPosition().distanceTo(e->getPosition()) <= range) {
            neighbors.push_back(e.get());
        }
    }

    return neighbors;
}

Vector2 Personage::choisirDirectionAleatoire() {

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, directions.size() - 1);

    size_t randomIndex = dist(gen);
    return directions[randomIndex];
}

bool Personage::isAlive() const {
    return health > 0;
}
