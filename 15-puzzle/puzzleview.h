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

class PuzzleView : public QWidget
{
    Q_OBJECT

public:
    explicit PuzzleView(QWidget *parent = nullptr);
    ~PuzzleView();
    void SetPuzzleView(QGridLayout* grid, QGraphicsView* view);
    void generateInitialPuzzle();
    void moveTile(Tile* tile, int row, int column);
    bool isMovebleLeft(int index);
    bool isMovebleRight(int index);
    bool isMovebleUp(int index);
    bool isMovebleDown(int index);
    void move(Tile* tile);
    void shuffleTiles();
    bool isSolvable();
    QVector<Tile*> get_buttons();
    void genInit();
    void removeWidgetAt(int row, int column);
private:
    QGridLayout* _grid;
    QGraphicsView* _view;
    QVector<Tile*> _buttons;
};

#endif // PUZZLEVIEW_H
