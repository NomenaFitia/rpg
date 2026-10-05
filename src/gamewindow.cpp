#include "gamewindow.h"
#include <QPainter>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>

GameWindow::GameWindow(Game& game, QWidget* parent)
    : QOpenGLWidget(parent), game(game) {
    setFixedSize(800, 600);
    connect(&game, &Game::gameUpdated, this, QOverload<>::of(&QOpenGLWidget::update));
}

GameWindow::~GameWindow() {
    vboAdventurer.destroy();
    vaoAdventurer.destroy();
    vboEnemy.destroy();
    vaoEnemy.destroy();
}

void GameWindow::initializeGL() {
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // shaders
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    shaderProgram->link();

    shaderProgram->bind();
    shaderProgram->setUniformValue("mvpMatrix", QMatrix4x4());
    shaderProgram->release();


    if (adventurerLoader.loadObj(":/models/enemy.obj")) {
        vaoAdventurer.create();
        vaoAdventurer.bind();

        vboAdventurer.create();
        vboAdventurer.bind();
        vboAdventurer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vboAdventurer.allocate(adventurerLoader.vertices.data(), adventurerLoader.vertices.size() * sizeof(QVector3D));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        vboAdventurer.release();
        vaoAdventurer.release();
    }

    if (enemyLoader.loadObj(":/models/enemy.obj")) {
        vaoEnemy.create();
        vaoEnemy.bind();

        vboEnemy.create();
        vboEnemy.bind();
        vboEnemy.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vboEnemy.allocate(enemyLoader.vertices.data(), enemyLoader.vertices.size() * sizeof(QVector3D));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        vboEnemy.release();
        vaoEnemy.release();
    }
}

void GameWindow::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    projection.setToIdentity();
    projection.perspective(45.0f, float(w) / float(h), 0.1f, 1000.0f);
}


void GameWindow::paintGL() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setupCamera();

    drawAdventurer();
    drawEnemies();
}


void GameWindow::drawAdventurer() {
    const Adventurer* adventurer = game.getMap().getAventurier();
    if (!adventurer) return;

    float x = adventurer->getPosition().x;
    float z = adventurer->getPosition().y;

    QMatrix4x4 modelMatrix;
    modelMatrix.translate(x, 0.5f, z);

    QMatrix4x4 mvp = projection * view * modelMatrix;
    shaderProgram->bind();
    shaderProgram->setUniformValue("mvpMatrix", mvp);

    shaderProgram->setUniformValue("inColor", QVector3D(0.0f, 0.5f, 1.0f));

    vaoAdventurer.bind();

    glDrawArrays(GL_TRIANGLES, 0, adventurerLoader.vertices.size());

    vaoAdventurer.release();
    shaderProgram->release();

    QString label = QString::number(adventurer->getLevel()) + " " +
                    QString::fromStdString(adventurer->getType()) +
                    " hp: " + QString::number(adventurer->getHealth());

    QVector3D screenPos = worldToScreen(x, z);

    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 8, QFont::Bold));
    painter.drawText(screenPos.x(), screenPos.y(), label);

    glEnable(GL_DEPTH_TEST);

}

void GameWindow::drawEnemies() {

    vaoEnemy.bind();
    shaderProgram->bind();

    for (auto it = game.getMap().beginEnemies(); it != game.getMap().endEnemies(); ++it) {
        const auto& enemy = *it;

        QMatrix4x4 modelMatrix;
        modelMatrix.translate(enemy->getPosition().x, 0.5f, enemy->getPosition().y);
        shaderProgram->setUniformValue("mvpMatrix", projection * view * modelMatrix);

        shaderProgram->setUniformValue("inColor", QVector3D(1.0f, 0.0f, 0.0f));

        glDrawArrays(GL_TRIANGLES, 0, enemyLoader.vertices.size());
    }

    shaderProgram->release();
    vaoEnemy.release();

    // 🔹 On fait l'affichage des labels **après** le rendu OpenGL
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 6));

    for (auto it = game.getMap().beginEnemies(); it != game.getMap().endEnemies(); ++it) {
        const auto& enemy = *it;

        QString label = QString::fromStdString(enemy->getType()) + " HP: " + QString::number(enemy->getHealth());
        QVector3D screenPos = worldToScreen(enemy->getPosition().x, enemy->getPosition().y);

        painter.drawText(screenPos.x(), screenPos.y(), label);
    }

    painter.end();  // 🔹 On s'assure que QPainter termine proprement
    glEnable(GL_DEPTH_TEST);  // 🔹 On réactive OpenGL après avoir utilisé QPainter
}

void GameWindow::setupCamera()
{
    const int gridWidth = game.getMap().getWidth();  // Largeur de la carte
    const int gridHeight = game.getMap().getHeight();  // Hauteur de la carte

    // Position de la caméra un peu plus éloignée pour voir l'ensemble de la scène
    view.setToIdentity();
    view.lookAt(QVector3D(gridWidth / 2.0f, gridHeight * 1.5f, gridHeight * 1.5f),  // Position de la caméra
                QVector3D(gridWidth / 2.0f, 0, gridHeight / 2.0f),     // Centre de la plateforme
                QVector3D(0, 1, 0));    // L'axe Y est vers le haut

    model.setToIdentity();
    model.rotate(-45, 1, 0, 0);  // Incliner la scène pour une vue isométrique
}


QVector3D GameWindow::worldToScreen(float x, float y) {
    QVector4D worldPos(x, 0.5f, y, 1.0f);  // Position en espace 3D
    QVector4D screenPos = projection * view * worldPos;
    screenPos /= screenPos.w();  // Normalisation des coordonnées homogènes

    float screenX = (screenPos.x() + 1.0f) * 0.5f * width();
    float screenY = (1.0f - screenPos.y()) * 0.5f * height();

    return QVector3D(screenX, screenY - 10, 0);
}
