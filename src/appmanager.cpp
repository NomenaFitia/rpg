#include "AppManager.h"
#include <QProcess>

AppManager::AppManager() {
    showCharacterSelection();
}

void AppManager::startGame(int characterType) {
    game = std::make_unique<Game>(Vector2(40, 40), characterType);

    gameWindow = std::make_unique<GameWindow>(*game);

    connect(game.get(), &Game::gameOver, this, &AppManager::showGameOver);
    gameWindow->show();

    timer = std::make_unique<QTimer>();
    connect(timer.get(), &QTimer::timeout, this, &AppManager::updateGame);
    timer->start(50);
}

void AppManager::showGameOver(int level) {
    gameWindow.reset();
    timer.reset();

    gameOverWindow = std::make_unique<GameOverWindow>(level);
    connect(gameOverWindow.get(), &GameOverWindow::replay, this, &AppManager::showCharacterSelection);
    gameOverWindow->show();
}

void AppManager::showCharacterSelection() {

    gameOverWindow.reset();
    characterSelectionWindow = std::make_unique<CharacterSelectionWindow>();
    connect(characterSelectionWindow.get(), &CharacterSelectionWindow::characterSelected, this, &AppManager::startGame);
    characterSelectionWindow->show();
}

void AppManager::updateGame() {
    if (game) {
        game->update();
    }
}
