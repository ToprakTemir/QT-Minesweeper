#include <iostream>
#include <random>
#include <unordered_set>

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QTimer>
#include <QVBoxLayout>
#include <QString>

#include "MineGrid.h"

using namespace std;

// MINESWEEPER PROJECT

static int BOARD_N = 20;
static int BOARD_M = 20;
static int INITIAL_NUM_MINES = 10;

int main(int argc, char *argv[]) {
    if (argc != 1 && argc != 4) {
        cout << "Usage: ./minesweeper [n] [m] [num_mines]" << endl;
        return 1;
    }
    if (argc == 4) {
        BOARD_N = std::stoi(argv[1]);
        BOARD_M = std::stoi(argv[2]);
        INITIAL_NUM_MINES = std::stoi(argv[3]);
    }

    QApplication app(argc, argv);

    // create the main window
    auto* window = new QWidget();
    window->setWindowTitle("MineSweeper");

    // create mine grid
    auto* mineGrid = new MineGrid(BOARD_N, BOARD_M, INITIAL_NUM_MINES);

    auto* mainLayout = new QVBoxLayout();

    // BUTTONS ON THE TOP

    auto* buttonsLayout = new QHBoxLayout();

    // TIMER

    static int timerValue = 0;
    auto* timer = new QTimer();
    auto* timerLabel = new QLabel("0");
    timer->start(1000);

    // connect the timer tick (every 1 second) with timerLabel and increment timerValue
    QObject::connect(timer, &QTimer::timeout, timerLabel, [=]() {
        timerLabel->setText(QString::number(timerValue++));
    });

    buttonsLayout->addWidget(timerLabel);


    // RESET BUTTON TODO: make it reset the board
    auto* restartButton = new QPushButton("Restart");
    buttonsLayout->addWidget(restartButton);

    QObject::connect(restartButton, &QPushButton::clicked, [=]() mutable{
        // reset timer
        timerValue = 0;
        timerLabel->setText(QString::number(timerValue));

        // reset board //TODO
        delete mineGrid;
        mineGrid = new MineGrid(BOARD_N, BOARD_M, INITIAL_NUM_MINES);
        mainLayout->addLayout(mineGrid);

    });


    // SCORE BUTTON  (score = numOfRevealedCells)

    static int score = 0;
    auto* scoreLabel = new QLabel("0");
    buttonsLayout->addWidget(scoreLabel);


    // QUIT BUTTON
    auto* quitButton = new QPushButton("Quit");
    buttonsLayout->addWidget(quitButton);
    QObject::connect(quitButton, &QPushButton::clicked, &QApplication::quit);


    // main mine layout of NxM buttons



    // final layout stuff

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(mineGrid);

    window->setLayout(mainLayout);

    int windowWidth = BOARD_N * Cell::cellSize;
    int windowHeight = BOARD_M * Cell::cellSize + 50;

    window->setFixedSize(windowWidth, windowHeight);
    window->show();
    return QApplication::exec();
}
