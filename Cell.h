
#ifndef QT_MINESWEEPER_CELL_H
#define QT_MINESWEEPER_CELL_H

#include <QPushButton>

class Cell : public QPushButton {

Q_OBJECT

public:
    const static int cellSize = 30;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int numOfAdjacentMines;

    Cell();
    ~Cell();

    void reveal();
    void toggleFlag();

signals:
    void mineClicked(Cell* cell);

public slots:
    void onCellClicked();
    void onCellRightClicked();
};

#endif //QT_MINESWEEPER_CELL_H
