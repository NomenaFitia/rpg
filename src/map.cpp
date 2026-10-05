#include "map.h"

Map::Map(Vector2 grid) : width(grid.x), height(grid.y), adventurer(nullptr) {}


void Map::placeAdventurer(std::unique_ptr<Adventurer>& a) {
    adventurer = a.get();
}

void Map::addEnemy(std::shared_ptr<Enemy> e) {
    enemies.push_back(e);
}

std::vector<std::shared_ptr<Enemy>>::iterator Map::removeEnemy(std::vector<std::shared_ptr<Enemy>>::iterator it) {
    return enemies.erase(it);
}

bool Map::isValidPosition(const Vector2& position) const {
    return position.x >= 0
           && position.x < width
           && position.y >= 0
           && position.y < height;
}

bool Map::isOccupied(const Vector2& position)  {

    if (adventurer->getPosition() == position) return true;

    for (auto& enemy : enemies)
    {
        if (enemy->getPosition() == position)return true;
    }

    return false;
}

int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }

const Adventurer *Map::getAventurier() const
{
    return adventurer;
}

std::vector<std::shared_ptr<Enemy> > &Map::getEnemies()
{
    return enemies;
}

