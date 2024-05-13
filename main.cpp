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

#include "Labels.h"

using namespace std;

// MINESWEEPER PROJECT

static int timerValue = 0;
static QLabel* timerLabel;

void setup_timer(QTimer* timer) {
    QObject::connect(timer, &QTimer::timeout, timerLabel, [=]() {
        timerLabel->setText(QString::number(timerValue++));
    });
}

static int BOARD_N = 10;
static int BOARD_M = 10;
static int INITIAL_NUM_MINES = 10;

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

    auto* layout = new QGridLayout();



    // TIMER

    QTimer* timer = new QTimer();
    timerLabel = new QLabel("0");
    timer->start(1000);
    setup_timer(timer);

    layout->addWidget(timerLabel);

    // add a restart button which resets the time
    QPushButton* restartButton = new QPushButton("Restart");
    layout->addWidget(restartButton);
    QObject::connect(restartButton, &QPushButton::clicked, [=](){
        timerValue = 0;
        timerLabel->setText(QString::number(timerValue));
    });


    // TODO: add a label to show the number of mines left



    // quit button
    QPushButton* quitButton = new QPushButton("Quit");
    layout->addWidget(quitButton);
    QObject::connect(quitButton, &QPushButton::clicked, &QApplication::quit);

    // TODO: create the main board of NxM buttons looking as empty.png

    vector<vector<QPushButton*>> unrevealedButtons(BOARD_N, vector<QPushButton*>(BOARD_M));

    QPixmap* unrevealed_square = new QPixmap("empty.png");

    layout->setSpacing(0);
    for (int i=1; i < BOARD_N; i++) {
        for (int j=1; j < BOARD_M; j++) {
            QPushButton* unrevealedButton = new QPushButton();
            unrevealedButtons[i][j] = unrevealedButton;
            unrevealedButton->setIcon(QIcon(*unrevealed_square));
            unrevealedButton->setIconSize(QSize(40, 80)); // TODO: bu sayılar hiçbir işe yaramıyo amk
            layout->addWidget(unrevealedButton, i, j);
        }
    }


    // randomly place the mines
    static int num_mines = INITIAL_NUM_MINES;

    if (num_mines > BOARD_N * BOARD_M) {
        cout << "Number of mines is greater than the board size" << endl;
        return 1;
    }

    // for any mine: (X, Y) = (mine_location / BOARD_N, mine_location % BOARD_N)
    unordered_set<int> mine_locations;

    // random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, BOARD_M * BOARD_N);

    for (int i=0; i < num_mines; i++) {
        int random_number = distr(gen);

        if (mine_locations.find(random_number) == mine_locations.end())
            mine_locations.insert(random_number);
        else
            i--; // try again for the same mine
    }

    window->setLayout(layout);
    window->show();
    return QApplication::exec();
}
