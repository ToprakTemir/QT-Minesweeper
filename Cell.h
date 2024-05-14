
#ifndef QT_MINESWEEPER_CELL_H
#define QT_MINESWEEPER_CELL_H

#include <QPushButton>

class Cell : public QPushButton {

Q_OBJECT

public:
    int x;
    int y; // grid[x][y] is used as the i and j indexes

    const static int cellSize = 30;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int numOfAdjacentMines;

    Cell(int, int);
    ~Cell();

    void reveal();
    void toggleFlag();

signals:
    void cellRevealed();
    void mineClicked(Cell* cell);
    void revealAdjacentEmptyCells(int x, int y);
    void revealedCellClicked(int x, int y);
    void cell_flagged();
    void cell_unflagged();

public slots:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif //QT_MINESWEEPER_CELL_H
