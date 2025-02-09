/****************************************************************************
** headerfile for 'minedistance.c'
**
** Created by: David Morra 2/5/2025
*****************************************************************************/

#ifndef MINEDISTANCE_H
#define MINEDISTANCE_H
#include <cstdlib>
#include <ctime>
#include <QDebug>

class MineDistance {
public:
    MineDistance();
    void reset();
    int getPos(int y, int x);
    void printBoard();


private:
    int countArround(int num);
    bool inBound(int x, int y);
    int *totalGrid = new int[480];
    void randNum();

};

#endif
