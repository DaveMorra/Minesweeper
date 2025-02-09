//David Morra 2/5/2025
//headerfile for maingame.c

#ifndef MAINGAME_H
#define MAINGAME_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <string>
#include "minedistance.h"

class MainGame : public QMainWindow
{
    Q_OBJECT

public:
    MineDistance *mineDis = new MineDistance();
    MainGame(QWidget *parent = nullptr);  // Constructor declaration
    void startGame();  // Starts the game and creates the window

private:
    void gameHeader();
    QWidget *gameWidget;  // The game widget (window)
    QGridLayout *gridLayout;  // Grid layout for the game window
    void resetGame();
    void necessaryLabels();
    bool inBound(int y, int x);
    int clearedTotal;
    QPushButton *buttons[480];
    bool activeButtons[480];
    QLabel *activeLabels[480];
    QLabel *labelScore;
    QLabel *labelStatus;
    void mousePressEvent(QMouseEvent *event);
    void mousePressEventLeft(int n);

};

#endif
