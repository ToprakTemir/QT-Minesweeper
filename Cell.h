
#ifndef QT_MINESWEEPER_CELL_H
#define QT_MINESWEEPER_CELL_H

#include <QPushButton>

class Cell : public QPushButton {

Q_OBJECT

public:
    int x; // the
    int y;
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
    void mineClicked(Cell* cell);
    void revealAdjacentEmptyCells(int x, int y);

public slots:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif //QT_MINESWEEPER_CELL_H
