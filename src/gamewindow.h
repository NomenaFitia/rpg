#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "Game.h"
#include "qmatrix4x4.h"
#include "qopenglshaderprogram.h"
#include "src/ObjectLoader.h"

class GameWindow : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit GameWindow(Game& game, QWidget* parent = nullptr);
    ~GameWindow();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    Game& game;
    QMatrix4x4 projection, view, model;
    QOpenGLShaderProgram* shaderProgram = nullptr;

    void drawAdventurer();
    void drawEnemies();
    void setupCamera();

    QOpenGLBuffer vboAdventurer;
    QOpenGLVertexArrayObject vaoAdventurer;
    ObjectLoader adventurerLoader;

    QOpenGLBuffer vboEnemy;
    QOpenGLVertexArrayObject vaoEnemy;
    ObjectLoader enemyLoader;
    QVector3D worldToScreen(float x, float y);
};

#endif
