//David Morra 2/5/2025
//file will hold main game operations and graphics
#include "maingame.h"

//constructor that will create the main screen window
MainGame::MainGame(QWidget *parent)
    : QMainWindow(parent),
      gameWidget(new QWidget(this)),
      gridLayout(new QGridLayout(gameWidget)) {

    //adjust parameters for the main screen
    setWindowTitle("Minesweeper");
    setFixedWidth(800);
    setFixedHeight(400);
    gridLayout->setSpacing(0);
    setCentralWidget(gameWidget);
}

//display all elements for the game page and create grid data
void MainGame::startGame()
{
    //create header for stats and reset button
    gameHeader();
    clearedTotal = 0;

    //create hidden labels for the distance between square and undiscovered nodes
    for (int i = 0; i < 480; i++) {
        activeLabels[i] = new QLabel("   " + QString::number(mineDis->getPos(i / 30, i % 30)) + " ", this);
        activeLabels[i]->hide();
    }

    //create a grid of buttons for undiscovered mines
    for (int i = 0; i < 480; i++) {
        buttons[i] = new QPushButton("");
        buttons[i]->setObjectName(QString::number(i));
        gridLayout->addWidget(buttons[i], (i / 30) + 2, i % 30);

        //enable connection for left click for a given button
        connect(buttons[i], &QPushButton::clicked, this, [this]()
                { mousePressEventLeft(std::stoi(sender()->objectName().toStdString())); });
    }

    //show main window
    show();
}
//display header with info above the tiles
void MainGame::gameHeader() {

    //add the required labels
    QLabel *empty = new QLabel("", this);
    gridLayout->addWidget(empty, 0, 0);
    gridLayout->addWidget(empty, 1, 0);
    QPushButton *buttonsReset = new QPushButton("Reset", this);
    buttonsReset->move(690, 5);
    labelStatus = new QLabel("Area Cleared\n", this);
    labelScore = new QLabel("\n0/381", this);
    labelScore->move(10, 5);
    labelStatus->move(10, 5);

    //when reset button is pressed, call reset game function
    connect(buttonsReset, &QPushButton::clicked, this, [this]() { resetGame(); });
}

//this function will reset the game and all variables
void MainGame::resetGame() {

    //generate new board
    mineDis->reset();

    //iterate each tile and hide all labels and show all undiscovered titles
    for (int i = 0; i < 480; i++) {
        activeLabels[i]->hide();
        activeLabels[i]->setText("   " + QString::number(mineDis->getPos(i / 30, i % 30)) + " ");
        buttons[i]->show();
        buttons[i]->setIcon(QIcon());
    }

    //reset score
    clearedTotal = 0;
    labelScore->setText("\n" + QString::number(clearedTotal) + "/381");
    labelStatus->setText("Area Cleared\n");
}

//function will determine if the distance from the bomb label is needed or can be removed
void MainGame::necessaryLabels() {

    //will iterate each title
    bool necessary = false;
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 30; x++) {

            //value will be set false to default, if nearby undiscovered tile, set to true, else hide the label
            necessary = false;
            if (inBound(y - 1, x - 1) && !(buttons[((y - 1) * 30) + (x - 1)]->isHidden())) { necessary = true; } // top left
            if (inBound(y - 1, x) && !(buttons[((y - 1) * 30) + (x)]->isHidden())) { necessary = true; }         // top middle
            if (inBound(y - 1, x + 1) && !(buttons[((y - 1) * 30) + (x + 1)]->isHidden())) { necessary = true; } // top right
            if (inBound(y, x - 1) && !(buttons[((y) * 30) + (x - 1)]->isHidden())) { necessary = true; }         // left
            if (inBound(y, x + 1) && !(buttons[((y) * 30) + (x + 1)]->isHidden())) { necessary = true; }         // right
            if (inBound(y + 1, x - 1) && !(buttons[((y + 1) * 30) + (x - 1)]->isHidden())) { necessary = true; } // bottom left
            if (inBound(y + 1, x) && !(buttons[((y + 1) * 30) + (x)]->isHidden())) { necessary = true; }         // bottom middle
            if (inBound(y + 1, x + 1) && !(buttons[((y + 1) * 30) + (x + 1)]->isHidden())) { necessary = true; } // bottom right
            if (!necessary) { activeLabels[(y * 30) + x]->hide(); }
        }
    }
}

//returns if a given coordinate is inbounds of the 16x30 grid
bool MainGame::inBound(int y, int x) {
    return (x >= 0 && x <= 29) && (y >= 0 && y <= 15);
}

//toggle image of a flag when the button is right-clicked
void MainGame::mousePressEvent(QMouseEvent *event) {

    //continue if the right button is pressed and the game is still active
    if (event->button() == Qt::RightButton) {
        if (clearedTotal == -1) { return; }

        //determine what tile was pressed and if it is on a valid square
        int x = (event->pos().x() - 10) / 26.3333333;
        int y = (event->pos().y() - 40) / 22.5;
        if (!inBound(y, x)) { return; }

        //if the button has no flag, add an image of a flag
        if (buttons[(y * 30) + x]->icon().isNull()){
            QPixmap pixmap("MSflag.jpg");
            QIcon ButtonIcon(pixmap);
            buttons[(y * 30) + x]->setIcon(ButtonIcon);
            buttons[(y * 30) + x]->setIconSize(QSize(14, 14));
        }
        else //if button does a flag, remove the flag image
        {
            buttons[(y * 30) + x]->setIcon(QIcon());
        }
    }
}

//function handles the left click of a given button
void MainGame::mousePressEventLeft(int i) {

    //if user has finnished the game or got eliminated, ignore left clicks on main grid
    if(clearedTotal == -1 || clearedTotal == 381) { return; }

    //handles left click on safe tile
    if (mineDis->getPos(i / 30, i % 30) != -1) {

        //update score and hide button, and show labels
        clearedTotal++;
        buttons[i]->hide();
        activeLabels[i]->show();
        if (clearedTotal == 381) { labelStatus->setText("Completed\n"); }
        labelScore->setText("\n" + QString::number(clearedTotal) + "/381");
        gridLayout->addWidget(activeLabels[i], (i / 30) + 2, i % 30);
        necessaryLabels();
    }
    //handles left click on bomb tile
    else {
        
        //clear score and create QIcon
        clearedTotal = -1;
        QPixmap pixmap("MSbomb.jpg");
        QIcon ButtonIcon(pixmap);
        labelStatus->setText("Play Again\n");

        //display all bombs
        for (int n = 0; n < 480; n++) {
            if (mineDis->getPos(n / 30, n % 30) == -1) {
                buttons[n]->setIcon(ButtonIcon);
                buttons[n]->setIconSize(QSize(14, 14));
            }
        }
    }
}