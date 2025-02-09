//David Morra 2/5/2025
//main function that creates main game
#include "main.h"

//run main game when launched
int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);
    MainGame* game = new MainGame;
    game->startGame();
    return prog.exec();
}
