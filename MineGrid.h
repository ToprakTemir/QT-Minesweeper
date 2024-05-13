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

using namespace std;

class MineGrid : public QGridLayout {
public:
    const int n;
    const int m;
    const int initial_num_mines;
    int num_of_revealed_cells;
    vector<vector<QPushButton*>> cells;

    MineGrid();
    ~MineGrid();






    bool isMine(int, int);
    int numOfAdjacentMines(int, int);

};



#endif //QT_MINESWEEPER_MINEGRID_H
