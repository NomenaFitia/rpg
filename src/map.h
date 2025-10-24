#ifndef MAP_H
#define MAP_H

#include "Vector2.h"
#include "src/Adventurer.h"
#include "src/Enemy.h"
#include <vector>

class Map {
public:
    Map(Vector2 grid);

    bool isValidPosition(const Vector2& position) const;
    bool isOccupied(const Vector2& position);
    void placeAdventurer(std::unique_ptr<Adventurer>& a);
    void addEnemy(std::shared_ptr<Enemy> e);
    std::vector<std::shared_ptr<Enemy>>::iterator removeEnemy(std::vector<std::shared_ptr<Enemy>>::iterator it);

    int getWidth() const;
    int getHeight() const;

    const Adventurer* getAventurier() const;
    std::vector<std::shared_ptr<Enemy>>& getEnemies();

    Vector2 direction;
    Vector2 newPos;

    using EnemyIterator = std::vector<std::shared_ptr<Enemy>>::const_iterator;

    EnemyIterator beginEnemies() const { return enemies.begin(); }
    EnemyIterator endEnemies() const { return enemies.end(); }

private:
    int width, height;

    std::vector<std::shared_ptr<Enemy>> enemies;
    Adventurer* adventurer;
};

#endif
