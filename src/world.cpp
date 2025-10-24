#include "src\world.h"
#include <iostream>

World::World(int width, int height) : width(width), height(height) {}

bool World::isOccupied(Vector2 position) const {
    for (const auto& entity : entities) {
        if (entity->getPosition() == position) {
            return true;
        }
    }
    return false;
}

void World::addEntity(Entity* entity) {
    if (!isOccupied(entity->getPosition())) {
        entities.push_back(std::unique_ptr<Entity>(entity));
    } else {
        std::cerr << "Error: Position (" << entity->getPosition().x << ", "
                  << entity->getPosition().y << ") is already occupied.\n";
    }
}

void World::removeEntity(Entity* entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [entity](const std::unique_ptr<Entity>& e) { return e.get() == entity; }),
                   entities.end());
}

void World::update() {
    // Placeholder pour les mises à jour automatiques
}

void World::render() {
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, '.'));

    for (const auto& entity : entities) {
        Vector2 pos = entity->getPosition();
        grid[pos.y][pos.x] = entity->getSymbol();
    }

    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "--------------------------\n";
}

const std::vector<std::unique_ptr<Entity> > &World::getEntities() const
{
    return entities;
}

int World::getWidth()
{
    return width;
}

int World::getHeight()
{
    return height;
}
