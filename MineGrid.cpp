#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

#include "Cell.h"
#include "MineGrid.h"

//TODO: used QPushButton instead of Cell to run the main.cpp. Change all to Cell

MineGrid::MineGrid(int board_n, int board_m, int initial_num_mines) {
    this->n = board_n;
    this->m = board_m;
    this->initial_num_mines = initial_num_mines;
    this->num_of_revealed_cells = 0;

    this->cells = vector<vector<Cell*>>(n, vector<Cell*>(m));

    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(0);


    // Setup Cells
    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {

            Cell* newCell = new Cell(i, j);
            cells[i][j] = newCell;

            newCell->setFixedSize(Cell::cellSize, Cell::cellSize);
            newCell->setStyleSheet("QPushButton {border-image: url(../assets/empty.png);}");

            if (isMine(i,j))
                newCell->isMine = true;
            newCell->numOfAdjacentMines = numOfAdjacentMines(i,j);

            QObject::connect(newCell, &Cell::mineClicked, this, &MineGrid::mineClicked);
            QObject::connect(newCell, &Cell::revealAdjacentEmptyCells, this, &MineGrid::revealAdjacentEmptyCells);

            this->addWidget(newCell, i, j);
        }
    }

    if (initial_num_mines > n * m)
        cout << "Number of mines is greater than the board size" << endl;

    // random number generator for placing mines
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, m * n - 1);

    for (int i=0; i < initial_num_mines; i++) {
        int random_number = distr(gen);

        if (mine_locations.find(random_number) == mine_locations.end())
            mine_locations.insert(random_number);
        else
            i--; // try again for the same mine
    }


}

MineGrid::~MineGrid() {
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            delete cells[i][j];
        }
    }
}

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

// TODO
void MineGrid::revealAdjacentEmptyCells(int x, int y) {
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            if (cells[x+i][y+j]->isRevealed)
                continue;
            cells[x+i][y+j]->reveal();
        }
}

// TODO
void MineGrid::mineClicked(Cell* cell) {

}




