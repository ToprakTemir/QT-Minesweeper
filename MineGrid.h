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
public:
    MineGrid(int, int, int); // n, m, num_mines
    ~MineGrid() override;

    int mine_size;
    int n;
    int m;
    int num_mines;
    int num_of_revealed_cells;
    vector<vector<QPushButton*>> unrevealedButtons;
    unordered_set<int> mine_locations;

    bool isMine(int, int);
    int numOfAdjacentMines(int,int);

};


#endif //QT_MINESWEEPER_MINEGRID_H
