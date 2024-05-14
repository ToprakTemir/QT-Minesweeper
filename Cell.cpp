
#include <QMouseEvent>

#include "MineGrid.h"
#include "Cell.h"
using namespace std;

Cell::Cell(int x, int y) {
    isMine = false;
    isRevealed = false;
    isFlagged = false;
    this->x = x;
    this->y = y;
    numOfAdjacentMines = -1;
    setFixedSize(cellSize, cellSize);
    setStyleSheet("QPushButton {border-image: url(../assets/empty.png);}");
}

Cell::~Cell() = default;

void Cell::reveal() {
    if (isRevealed) return;
    if (isFlagged) return;
    isRevealed = true;

    if (isMine) {
        setStyleSheet("QPushButton {border-image: url(../assets/mine.png);}");
        emit mineClicked(this);
    }
    else {
        emit cellRevealed();
        if (numOfAdjacentMines == 0)
            emit revealAdjacentEmptyCells(this->x, this->y);

        string imgPath = "../assets/" + to_string(numOfAdjacentMines) + ".png";
        setStyleSheet(("QPushButton {border-image: url(" + imgPath + ");}").c_str());
    }
}

void Cell::toggleFlag() {
    if (isRevealed) return;
    if (isFlagged) {
        isFlagged = false;
        setStyleSheet("QPushButton {border-image: url(../assets/empty.png);}");
    }
    else {
        isFlagged = true;
        setStyleSheet("QPushButton {border-image: url(../assets/flag.png);}");
    }
}

void Cell::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) { // right click
        if (MineGrid::game_over) return;
        if (!isRevealed)
            toggleFlag();
    }
    else { // left click
        if (MineGrid::game_over) return;
        if (isFlagged) return;
        if (isRevealed) {
            emit revealedCellClicked(this->x, this->y);
        }
        else
            reveal();
    }
    QPushButton::mousePressEvent(event);
}




