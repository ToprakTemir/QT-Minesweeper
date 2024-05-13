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
    MineGrid();
    ~MineGrid();


private:
    const int mineSize;
    int n;
    int m;
    const int num_mines;
    int num_of_revealed_cells;
    vector<vector<QPushButton*>> unrevealedButtons;
    unordered_set<int> mine_locations;




    bool isMine(int, int, unordered_set<int>&);
    int numOfAdjacentMines(int,int,unordered_set<int>&);











};



#endif //QT_MINESWEEPER_MINEGRID_H
