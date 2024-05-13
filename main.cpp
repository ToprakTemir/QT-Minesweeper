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
#include "Cell.h"
#include "MineGrid.h"

using namespace std;

// MINESWEEPER PROJECT

static int timerValue = 0;
static QLabel* timerLabel;

void setup_timer(QTimer* timer) {
    QObject::connect(timer, &QTimer::timeout, timerLabel, [=]() {
        timerLabel->setText(QString::number(timerValue++));
    });
}

static int BOARD_N = 20;
static int BOARD_M = 20;
static int INITIAL_NUM_MINES = 50;
static int numOfRevealedCells = 0;

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

    auto* timer = new QTimer();
    timerLabel = new QLabel("0");
    timer->start(1000);
    setup_timer(timer);

    buttonsLayout->addWidget(timerLabel);

    // add a restart button which resets the time (for now), TODO: make it reset the board
    QPushButton* restartButton = new QPushButton("Restart");
    buttonsLayout->addWidget(restartButton);
    QObject::connect(restartButton, &QPushButton::clicked, [=](){
        timerValue = 0;
        timerLabel->setText(QString::number(timerValue));
    });

    // SCORE BUTTON  (score = numOfRevealedCells)


    // QUIT BUTTON
    auto* quitButton = new QPushButton("Quit");
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
