#ifndef GAME_H
#define GAME_H

#include "map.h"
#include <QTimer>

class Game : public QObject {
    Q_OBJECT;

public:
    Game(Vector2 grid, int characterType);
    void update();

    const Map& getMap() const;

signals:
    void gameUpdated();
    void gameOver(int level);

private:
    Map map;
    std::shared_ptr<Enemy> createRandomEnemy(Vector2 Position, int level);
    void spawnEnemies(int count);
    void handleCombat();

    Vector2 direction;
    Vector2 newPos;

    std::unique_ptr<Adventurer> adventurer;
};

#endif
