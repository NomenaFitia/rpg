#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include <memory>
#include <QTimer>
#include "game.h"
#include "gamewindow.h"
#include "characterselectionwindow.h"
#include "gameoverwindow.h"

class AppManager : public QObject {
    Q_OBJECT

public:
    AppManager();

private slots:
    void startGame(int characterType);
    void showGameOver(int level);
    void showCharacterSelection();
    void updateGame();

private:
    std::unique_ptr<CharacterSelectionWindow> characterSelectionWindow;
    std::unique_ptr<GameWindow> gameWindow;
    std::unique_ptr<GameOverWindow> gameOverWindow;
    std::unique_ptr<Game> game;
    std::unique_ptr<QTimer> timer;
};

#endif
