/****************************************************************************
** Main file 'minedistance.cpp'
**
** Created by: David Morra 2/5/2025
**
** This file will generate the board and keep track of board data
*****************************************************************************/
#include "minedistance.h"

//constructer that will generate a board
MineDistance::MineDistance() {
    reset();
}

//reset entire board
void MineDistance::reset() {
    randNum();
    for(int num = 0; num < 480; num++) {totalGrid[num] = countArround(num);}
}

//return count 0-8 for a tile, or if its a bomb -1
int MineDistance::getPos(int y, int x) {
    return totalGrid[(y*30) + x];
}

//randomly generate a board with 100 bombs
void MineDistance::randNum() {

   //reset the board and generate a random seed
   for(int num = 0; num < 480; num++) {totalGrid[num] = 0;}
   srand(time(0));
   int randNum = rand() % 480;

    //select 100 squares to be bombs
    for(int num = 0; num < 99; num++) {
        randNum  = (randNum  + (rand() % 10000)) % 480;
        if(totalGrid[randNum] != -1) {totalGrid[randNum] = -1;}
        else { --num;}
    }
}

//prints board used for testing
void MineDistance::printBoard() {
    for(int num = 0; num < 480; num++) {qDebug() << totalGrid[num];}
}

//counts the number of bombs around a single tile
int MineDistance::countArround(int num) {
    if(totalGrid[num] == -1) {return -1;}

    int total = 0;
    int x = num%30;
    int y = num/30;

    if(inBound(y-1, x-1) && getPos(y-1, x-1) == -1) {total++;} //top left
    if(inBound(y-1, x) && getPos(y-1, x) == -1) {total++;} //top middle
    if(inBound(y-1, x+1) && getPos(y-1, x+1) == -1) {total++;} //top right
    if(inBound(y, x-1) && getPos(y, x-1) == -1) {total++;} //left
    if(inBound(y, x+1) && getPos(y, x+1) == -1) {total++;} //right
    if(inBound(y+1, x-1) && getPos(y+1, x-1) == -1) {total++;} //bottom left
    if(inBound(y+1, x) && getPos(y+1, x) == -1) {total++;} //bottom middle
    if(inBound(y+1, x+1) && getPos(y+1, x+1) == -1) {total++;} //bottom right

    return total;
}

//returns if a given coordinate is inbounds of the 16x30 grid
bool MineDistance::inBound(int y, int x) {
    return (x >= 0 && x <= 29) && (y >= 0 && y <= 15);
}
