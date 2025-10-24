#include "CharacterSelectionWindow.h"
#include "qcoreevent.h"

CharacterSelectionWindow::CharacterSelectionWindow(QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("Choisissez votre personnage");
    setFixedSize(400, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);

    tankLabel = new QLabel(this);
    QPixmap tankPixmap(":/images/tank.png");

    if (tankPixmap.isNull()){
            qDebug() << "Erreur";
        }

    tankLabel->setPixmap(tankPixmap.scaled(150, 150, Qt::KeepAspectRatioByExpanding));
    tankLabel->setAlignment(Qt::AlignCenter);
    tankLabel->setObjectName("Tank");
    tankLabel->installEventFilter(this);
    layout->addWidget(tankLabel);


    QLabel* tankTextLabel = new QLabel("Tank", this);
    tankTextLabel->setAlignment(Qt::AlignCenter);
    tankTextLabel->setStyleSheet("color: black; font: bold 24px;");
    layout->addWidget(tankTextLabel);

    assassinLabel = new QLabel(this);
    QPixmap assassinPixmap(":/images/assassin.png");

    if (assassinPixmap.isNull()){
        qDebug() << "Erreur";
    }

    assassinLabel->setPixmap(assassinPixmap.scaled(150, 150, Qt::KeepAspectRatioByExpanding));
    assassinLabel->setAlignment(Qt::AlignCenter);
    assassinLabel->setObjectName("Assassin");
    assassinLabel->installEventFilter(this);
    layout->addWidget(assassinLabel);

    QLabel* assassinTextLabel = new QLabel("Assassin", this);
    assassinTextLabel->setAlignment(Qt::AlignCenter);
    assassinTextLabel->setStyleSheet("color: black; font: bold 24px;");
    layout->addWidget(assassinTextLabel);

    layout->setAlignment(Qt::AlignCenter);

}

bool CharacterSelectionWindow::eventFilter(QObject* watched, QEvent* event) {
    if (event->type() == QEvent::MouseButtonPress) {
        if (watched == tankLabel) {
            emit characterSelected(1); // Tank
            close();
            return true;
        } else if (watched == assassinLabel) {
            emit characterSelected(2); // Assassin
            close();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}
