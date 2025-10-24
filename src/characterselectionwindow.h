#ifndef CHARACTERSELECTIONWINDOW_H
#define CHARACTERSELECTIONWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CharacterSelectionWindow : public QWidget {
    Q_OBJECT
public:
    explicit CharacterSelectionWindow(QWidget* parent = nullptr);
    bool eventFilter(QObject* watched, QEvent* event) override;

signals:
    void characterSelected(int type); // 1 = Tank, 2 = Assassin

private:
    QLabel* tankLabel;
    QLabel* assassinLabel;
};

#endif
