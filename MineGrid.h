#ifndef QT_MINESWEEPER_MINEGRID_H
#define QT_MINESWEEPER_MINEGRID_H

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

using namespace std;

class MineGrid : public QGridLayout {

Q_OBJECT

public:
    MineGrid(int, int, int); // n, m, num_mines
    ~MineGrid() override;

    int n;
    int m;
    int initial_num_mines;
    int num_of_revealed_cells;

    vector<vector<Cell*>> cells;
    unordered_set<int> mine_locations;

    bool isMine(int, int);
    int numOfAdjacentMines(int,int);
    void revealAdjacentEmptyCells(int, int);
    void mineClicked(Cell*);
};


#endif //QT_MINESWEEPER_MINEGRID_H
