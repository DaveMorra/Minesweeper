/****************************************************************************
** Main file 'maingame.cpp'
**
** Created by: David Morra 2/5/2025
**
** Main function that creates main window and calls to start the game
*****************************************************************************/

#include "main.h"

//run main game when launched
int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);
    MainGame* game = new MainGame;
    game->startGame();
    return prog.exec();
}
