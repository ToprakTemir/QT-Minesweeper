
#ifndef QT_MINESWEEPER_CELL_H
#define QT_MINESWEEPER_CELL_H

#include <QPushButton>

class Cell : public QPushButton {
public:
    const int cellSize;
    const bool isMine;
    bool isRevealed;
    bool isFlagged;
    int numOfAdjacentMines;

    Cell();
    ~Cell();

    void reveal();
    void toggleFlag();

public slots:
    void onCellClicked();
    void onCellRightClicked();
};

#endif //QT_MINESWEEPER_CELL_H
