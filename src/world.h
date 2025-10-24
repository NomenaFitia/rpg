#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include <vector>
#include <memory>

class World {
private:
    int width;
    int height;
    std::vector<std::unique_ptr<Entity>> entities;

public:
    World(int width, int height);

    bool isOccupied(Vector2 position) const;
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);

    void update();
    void render();
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    int getWidth();
    int getHeight();
};

#endif // WORLD_H
