#include "Game.h"
#include "src/adventurerType/assassin.h"
#include "src/adventurerType/tank.h"
#include "src/combatsystem.h"
#include <iostream>
#include <ostream>

Game::Game(Vector2 grid, int characterType) : map(grid){
    Vector2 position(1,1);

    if (characterType == 1)
        adventurer = std::make_unique<Tank>(position);

    if (characterType == 2)
        adventurer = std::make_unique<Assassin>(position);

    map.placeAdventurer(adventurer);
    spawnEnemies(10);

}

void Game::spawnEnemies(int count) {
    for (int i = 0; i < count; i++) {
        int x = rand() % map.getWidth();
        int y = rand() % map.getHeight();
        auto enemy = createRandomEnemy(Vector2(x,y), adventurer->getLevel());
        map.addEnemy(enemy);
    }
}

std::shared_ptr<Enemy> Game::createRandomEnemy(Vector2 position, int level) {

    int enemyType = rand() % 4;

    switch (enemyType) {
    case 0:
        return std::make_shared<Enemy>(std::string("skeleton"), position, 5 + (2*level), 1 + (2*level), 1);
    case 1:
        return std::make_shared<Enemy>(std::string("gobelin"), position, 15 + (2*level), 3 + (2*level), 2);
    case 2:
        return std::make_shared<Enemy>(std::string("golem"), position, 30 + (2*level), 5 + (2*level), 5);
    case 3:
        return std::make_shared<Enemy>(std::string("Bellion"), position, 60 + (2*level), 15 + (2*level), 10);
    default:
        return std::make_shared<Enemy>(std::string("God"), position, 1000, 50, 1);
    }
}


void Game::handleCombat() {
    for (auto it = map.getEnemies().begin(); it != map.getEnemies().end(); ) {
        auto& enemy = *it;

        if (adventurer->getPosition().isInRange(enemy->getPosition(), 1)) {

            CombatSystem combatSystem(adventurer.get(), enemy.get());
            combatSystem.startCombat();

            if (!enemy->isAlive()) {
                it = map.removeEnemy(it);
            } else {
                ++it;
            }

            break;
        } else {
            ++it;
        }
    }

}

void Game::update() {

    do {
        direction =  Adventurer::choisirDirectionAleatoire();
        newPos = adventurer->getPosition() + direction;
    }
    while ( !map.isValidPosition(newPos) || map.isOccupied(newPos));

    adventurer->move(direction);

    for (auto& enemy : map.getEnemies()) {

        do {
        direction =  Enemy::choisirDirectionAleatoire();
            newPos = enemy->getPosition() + direction;
        }
        while ( !map.isValidPosition(newPos) || map.isOccupied(newPos));

        enemy->move(direction);
    }

    if (!adventurer->isAlive()) {
        std::cout << "Game Over ! L'aventurier est Mort" << std::endl;

        emit gameOver(adventurer->getLevel());
    }

    handleCombat();

    if (map.getEnemies().size() < 3 ) spawnEnemies(10 + adventurer->getLevel());

    emit gameUpdated();
}

const Map& Game::getMap() const {
    return map;
}
