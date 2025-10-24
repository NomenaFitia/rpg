#include "GameOverWindow.h"

GameOverWindow::GameOverWindow(int level, QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("Game Over");
    setFixedSize(400, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* levelLabel = new QLabel("Niveau atteint : " + QString::number(level), this);
    levelLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(levelLabel);

    gameOverImage = new QLabel(this);
    QPixmap gameOverPixmap(":/images/gameover.png");
    gameOverImage->setPixmap(gameOverPixmap.scaled(200, 150, Qt::KeepAspectRatio));
    gameOverImage->setAlignment(Qt::AlignCenter);
    layout->addWidget(gameOverImage);

    replayButton = new QPushButton("Rejouer", this);
    layout->addWidget(replayButton, 0, Qt::AlignCenter);

    connect(replayButton, &QPushButton::clicked, this, &GameOverWindow::replay);
}
