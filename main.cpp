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

    QTimer* timer = new QTimer();
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
    QPushButton* quitButton = new QPushButton("Quit");
    buttonsLayout->addWidget(quitButton);
    QObject::connect(quitButton, &QPushButton::clicked, &QApplication::quit);


    // main mine layout of NxM buttons

    auto* minesLayout = new QGridLayout();

    vector<vector<QPushButton*>> unrevealedButtons(BOARD_N, vector<QPushButton*>(BOARD_M));

    QString currentDir = QDir::currentPath();
    QString imageAbsolutePath = currentDir + "/../assets/empty.png";
    QPixmap* unrevealed_square_img = new QPixmap(imageAbsolutePath);
    if (unrevealed_square_img->isNull()) {
        cout << "Image not found" << endl;
        return 1;
    }

    int mineSize = 30;

    minesLayout->setContentsMargins(0, 0, 0, 0);
    minesLayout->setSpacing(0);

    for (int i=0; i < BOARD_N; i++) {
        for (int j=0; j < BOARD_M; j++) {

            QPushButton* unrevealedButton = new QPushButton();
            unrevealedButtons[i][j] = unrevealedButton;

            //connect on click to change icon

            QObject::connect(unrevealedButton, &QPushButton::clicked, [=]() {
                unrevealedButton->setIcon(QIcon(currentDir + "/../assets/0.png"));
            });



            unrevealedButton->setFixedSize(mineSize, mineSize);
            unrevealedButton->setStyleSheet("QPushButton {"
                                 "border-image: url(../assets/empty.png);"
                                 "}");

            minesLayout->addWidget(unrevealedButton, i, j);
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



    // final layout stuff

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(minesLayout);

    window->setLayout(mainLayout);

    int windowWidth = BOARD_N * mineSize;
    int windowHeight = BOARD_M * mineSize + 50;

    window->setFixedSize(windowWidth, windowHeight);
    window->show();
    return QApplication::exec();
}
