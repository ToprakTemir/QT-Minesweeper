
#include "MineGrid.h"
#include "Cell.h"
using namespace std;

Cell::Cell() {
    isMine = false;
    isRevealed = false;
    isFlagged = false;
    numOfAdjacentMines = -1;
    setFixedSize(cellSize, cellSize);
    setStyleSheet("QPushButton {border-image: url(../assets/empty.png);}");

    connect(this, SIGNAL(clicked()), this, SLOT(onCellClicked()));
    connect(this, SIGNAL(rightClicked()), this, SLOT(onCellRightClicked()));
}

Cell::~Cell() {
    disconnect(this, SIGNAL(clicked()), this, SLOT(onCellClicked()));
    disconnect(this, SIGNAL(rightClicked()), this, SLOT(onCellRightClicked()));
}

void Cell::reveal() {
    if (isRevealed) return;
    isRevealed = true;

    if (isMine) {
        setStyleSheet("QPushButton {border-image: url(../assets/mine.png);}");
        emit mineClicked(this);
    }
    else {
//        TODO: if (numOfAdjacentMines == 0)
            // emit signal to board to reveal all adjacent cells

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

void Cell::onCellClicked() {
    if (isFlagged) return;
    if (isRevealed) return;
    reveal();
}

void Cell::onCellRightClicked() {
    if (!isRevealed)
        toggleFlag();
}



