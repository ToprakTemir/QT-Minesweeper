#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>
#include <utility>

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QTimer>
#include <QVBoxLayout>
#include <Qdir>
#include <QString>
#include <QPixmap>

#include "Labels.h"
#include "MineGrid.h"

using namespace std;

// MINESWEEPER PROJECT

static int BOARD_N = 20;
static int BOARD_M = 20;
static int INITIAL_NUM_MINES = 50;
static int numOfRevealedCells = 0;

bool isMine(int x, int y, unordered_set<int>& mine_locations) {
    return mine_locations.find(x * BOARD_N + y) != mine_locations.end();
}

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

    auto* mainLayout = new QVBoxLayout();


    // BUTTONS ON THE TOP

    auto* buttonsLayout = new QHBoxLayout();

    // TIMER

    static int timerValue = 0;
    QTimer* timer = new QTimer();
    QLabel* timerLabel = new QLabel("0");
    timer->start(1000);

    // connect the timer tick (every 1 second) with timerLabel and increment timerValue
    QObject::connect(timer, &QTimer::timeout, timerLabel, [=]() {
        timerLabel->setText(QString::number(timerValue++));
    });

    buttonsLayout->addWidget(timerLabel);


    // RESET BUTTON TODO: make it reset the board
    QPushButton* restartButton = new QPushButton("Restart");
    buttonsLayout->addWidget(restartButton);

    QObject::connect(restartButton, &QPushButton::clicked, [=](){
        // reset timer
        timerValue = 0;
        timerLabel->setText(QString::number(timerValue));

        // reset board //TODO
    });


    // SCORE BUTTON  (score = numOfRevealedCells)

    static int score = 0;
    QLabel* scoreLabel = new QLabel("0");
    buttonsLayout->addWidget(scoreLabel);


    // QUIT BUTTON
    QPushButton* quitButton = new QPushButton("Quit");
    buttonsLayout->addWidget(quitButton);
    QObject::connect(quitButton, &QPushButton::clicked, &QApplication::quit);


    // main mine layout of NxM buttons

    auto* mineGrid = new MineGrid(BOARD_N, BOARD_M, INITIAL_NUM_MINES);

    // final layout stuff

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(mineGrid);

    window->setLayout(mainLayout);

    int windowWidth = BOARD_N * mineGrid->mine_size;
    int windowHeight = BOARD_M * mineGrid->mine_size + 50;

    window->setFixedSize(windowWidth, windowHeight);
    window->show();
    return QApplication::exec();
}
