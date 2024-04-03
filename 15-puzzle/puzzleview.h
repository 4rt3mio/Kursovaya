#ifndef PUZZLEVIEW_H
#define PUZZLEVIEW_H

#include <QGridLayout>
#include <QObject>
#include <QGridLayout>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <random>
#include <algorithm>
#include "tile.h"

class PuzzleView
{
public:
    PuzzleView(QGridLayout* grid, QGraphicsView* view);
    void generateInitialPuzzle();
    void moveTile(Tile* tile, int row, int column);
    bool isMoved(int index);
    void move(int _ind);
    void shuffleTiles();
    bool isSolvable();
    QVector<Tile*> get_buttons();
    void genInit();
private:
    QGridLayout* _grid;
    QGraphicsView* _view;
    QVector<Tile*> _buttons;
};

#endif // PUZZLEVIEW_H
