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

#include "Cell.h"
#include "MineGrid.h"

//TODO: used QPushButton instead of Cell to run the main.cpp. Change all to Cell

MineGrid::MineGrid(int board_n, int board_m, int initial_num_mines) {
    n = board_n;
    m = board_m;
    num_mines = initial_num_mines;
    num_of_revealed_cells = 0;
    mine_size = 30;

    vector<vector<QPushButton*>> unrevealedButtons(n, vector<QPushButton*>(m));

    QString currentDir = QDir::currentPath();
    QString imageAbsolutePath = currentDir + "/../assets/empty.png";
    QPixmap* unrevealed_square_img = new QPixmap(imageAbsolutePath);

    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(0);

    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {

            QPushButton* unrevealedButton = new QPushButton();
            unrevealedButtons[i][j] = unrevealedButton;

            unrevealedButton->setFixedSize(mine_size, mine_size);
            unrevealedButton->setStyleSheet("QPushButton {"
                                            "border-image: url(../assets/empty.png);"
                                            "}");

            this->addWidget(unrevealedButton, i, j);
        }
    }

    if (num_mines > n * m) {
        cout << "Number of mines is greater than the board size" << endl;
    }

    // random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, m * n - 1);

    for (int i=0; i < num_mines; i++) {
        int random_number = distr(gen);

        if (mine_locations.find(random_number) == mine_locations.end())
            mine_locations.insert(random_number);
        else
            i--; // try again for the same mine
    }
}

MineGrid::~MineGrid() {}

bool MineGrid::isMine(int x, int y) {
    return mine_locations.find(x * n + y) != mine_locations.end();
}

int MineGrid::numOfAdjacentMines(int x, int y) {
    int result = 0;
    for (int i = -1; i<=1; i++)
        for (int j = -1; j<=1; j++) {
            if (i == 0 && j == 0)
                continue;
            if (isMine(x+i, y+j))
                result++;
        }
    return result;
}




