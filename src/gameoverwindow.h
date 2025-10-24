#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>

class GameOverWindow : public QWidget {
    Q_OBJECT
public:
    explicit GameOverWindow(int level, QWidget* parent = nullptr);

signals:
    void replay();

private:
    QPushButton* replayButton;
    QLabel* gameOverImage;
};

#endif
