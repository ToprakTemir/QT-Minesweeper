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
#include <QMainWindow>

#include "Cell.h"
#include "MineGrid.h"

using namespace std;

// MINESWEEPER PROJECT

static int BOARD_N = 20;
static int BOARD_M = 20;
static int INITIAL_NUM_MINES = 5;

int MineGrid::game_over = 1;

void connectCellsWithScoreAndRemainingMinesLabels(MineGrid* mineGrid, QLabel* scoreLabel, QLabel* remainingMinesLabel) {
    for (int i = 0; i < BOARD_N; i++) {
        for (int j = 0; j < BOARD_M; j++) {
            QObject::connect(mineGrid->cells[i][j], &Cell::cellRevealed, scoreLabel, [=]() {
                scoreLabel->setText("Score: " + QString::number(++mineGrid->num_of_revealed_cells));
            });
            QObject::connect(mineGrid->cells[i][j], &Cell::cell_flagged, remainingMinesLabel, [=]() {
                remainingMinesLabel->setText("Remaining Mines: " + QString::number(INITIAL_NUM_MINES - (++mineGrid->num_of_flagged_cells)));
            });
            QObject::connect(mineGrid->cells[i][j], &Cell::cell_unflagged, remainingMinesLabel, [=]() {
                remainingMinesLabel->setText("Remaining Mines: " + QString::number(INITIAL_NUM_MINES - (--mineGrid->num_of_flagged_cells)));
            });
        }
    }
}

void gameEndSignals_setup(MineGrid* mineGrid, QTimer* timer) {
    //game lost
    QObject::connect(mineGrid, &MineGrid::gameLost, [=]() mutable{
        // pop up
        auto *popUp = new QLabel("   You lost.");
        popUp->setGeometry(750, 500, 100, 50);
        popUp->show();
        // stop time
        timer->stop();
    });

    // game won
    QObject::connect(mineGrid, &MineGrid::gameWon, [=]() mutable {
        auto *popUp = new QLabel("   You won.");
        popUp->setGeometry(750, 500, 100, 50);
        popUp->show();
        timer->stop();
    });
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

    // create mine grid
    auto* mineGrid = new MineGrid(BOARD_N, BOARD_M, INITIAL_NUM_MINES);

    auto* mainLayout = new QVBoxLayout();

    // BUTTONS ON THE TOP

    auto* buttonsLayout = new QHBoxLayout();

    // TIMER

    static int timerValue = 0;
    auto* timer = new QTimer();
    auto* timerLabel = new QLabel("Time: " + QString::number(timerValue));
    timer->start(1000);

    // connect the timer tick (every 1 second) with timerLabel and increment timerValue
    QObject::connect(timer, &QTimer::timeout, timerLabel, [=]() {
        timerLabel->setText("Time: " + QString::number(timerValue++));
    });

    buttonsLayout->addWidget(timerLabel);

    // SCORE BUTTON  (score = numOfRevealedCells)

    auto* scoreLabel = new QLabel("0");
    buttonsLayout->addWidget(scoreLabel);

    // REMAINING MINES LABEL

    auto *remainingMinesLabel = new QLabel("Remaining Mines: " + QString::number(INITIAL_NUM_MINES));
    buttonsLayout->addWidget(remainingMinesLabel);

    connectCellsWithScoreAndRemainingMinesLabels(mineGrid, scoreLabel, remainingMinesLabel);

    // RESET BUTTON
    auto* restartButton = new QPushButton("Restart");
    buttonsLayout->addWidget(restartButton);

    QObject::connect(restartButton, &QPushButton::clicked, [=]() mutable{
        // reset timer
        timer->start(1000);
        timerValue = 0;
        timerLabel->setText("Time: " + QString::number(timerValue));

        // reset score
        mineGrid->num_of_revealed_cells = 0;
        scoreLabel->setText("Score: " + QString::number(mineGrid->num_of_revealed_cells));

        // reset board
        delete mineGrid;
        mineGrid = new MineGrid(BOARD_N, BOARD_M, INITIAL_NUM_MINES);

        connectCellsWithScoreAndRemainingMinesLabels(mineGrid, scoreLabel, remainingMinesLabel);

        gameEndSignals_setup(mineGrid, timer);

        mainLayout->addLayout(mineGrid);

    });

    // HINT BUTTON
    auto* hintButton = new QPushButton("Hint");
    QObject::connect(hintButton, &QPushButton::clicked, mineGrid, &MineGrid::giveHint);
    buttonsLayout->addWidget(hintButton);

    // QUIT BUTTON
    auto* quitButton = new QPushButton("Quit");
    buttonsLayout->addWidget(quitButton);
    QObject::connect(quitButton, &QPushButton::clicked, &QApplication::quit);


    gameEndSignals_setup(mineGrid, timer);

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
