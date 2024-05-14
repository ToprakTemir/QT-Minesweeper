#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

#include "Cell.h"
#include "MineGrid.h"

//TODO: used QPushButton instead of Cell to run the main.cpp. Change all to Cell

MineGrid::MineGrid(int board_n, int board_m, int initial_num_mines) {
    n = board_n;
    m = board_m;
    game_over = 0;
    this->n = board_n;
    this->m = board_m;
    this->initial_num_mines = initial_num_mines;
    num_of_revealed_cells = 0;
    num_of_flagged_cells = 0;
    hintCell_x = -1;
    hintCell_y = -1;

    cells = vector<vector<Cell*>>(n, vector<Cell*>(m));

    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(0);

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
            QObject::connect(newCell, &Cell::revealedCellClicked, this, &MineGrid::revealCellsIfAllNearbyCellsFlagged);
            QObject::connect(newCell, &Cell::cellRevealed, this, &MineGrid::checkWinCondition);
            this->addWidget(newCell, i, j);
        }
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
            if (x+i<0 || x+i == n || y+j<0 || y+j == m)
                continue;
            if (i == 0 && j == 0)
                continue;
            if (isMine(x+i, y+j))
                result++;
        }
    return result;
}

void MineGrid::revealAdjacentEmptyCells(int x, int y) {
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            if (x+i<0 || x+i == n || y+j<0 || y+j == m)
                continue;
            if (cells[x+i][y+j]->isRevealed)
                continue;
            cells[x+i][y+j]->reveal();
        }
}

int MineGrid::numOfNearbyFlags(int x, int y) {
    int result = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            if (x+i<0 || x+i == n || y+j<0 || y+j == m)
                continue;
            if (cells[x+i][y+j]->isFlagged)
                result++;
        }
    return result;
}

int MineGrid::numOfNearbyUnrevealedCells(int x, int y) {
    int result = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            if (x+i<0 || x+i == n || y+j<0 || y+j == m)
                continue;
            if (!cells[x+i][y+j]->isRevealed)
                result++;
        }
    return result;
}

void MineGrid::revealCellsIfAllNearbyCellsFlagged(int x, int y) {
    if (numOfNearbyFlags(x, y) == cells[x][y]->numOfAdjacentMines) {
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) {
                if (x+i<0 || x+i == n || y+j<0 || y+j == m)
                    continue;
                cells[x+i][y+j]->reveal();
            }
    }
}
// hint feature is not perfect, and only able to show simple hints
void MineGrid::giveHint() {
    if (hintCell_x != -1 && hintCell_y != -1 && !cells[hintCell_x][hintCell_y]->isRevealed) {
        cells[hintCell_x][hintCell_y]->reveal();
        return;
    }

    for (int x=0; x<n; x++) {
        for (int y=0; y<m; y++) {

        }
    }
}


// lose game
void MineGrid::mineClicked(Cell* cell) {
    revealAllMines();

    //all cells unclickable
    game_over = 1;

    //stop timer in main.cpp
    emit gameLost();
}


void MineGrid::checkWinCondition() {
    cout << num_of_revealed_cells << endl;
    if (num_of_revealed_cells + 1 == n * m - initial_num_mines) {
        revealAllMines();
        game_over = 1;
        emit gameWon();
    }
}

void MineGrid::revealAllMines() {
    for (int i=0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (cells[i][j]->isMine)
                cells[i][j]->setStyleSheet("QPushButton {border-image: url(../assets/mine.png);}");
}


