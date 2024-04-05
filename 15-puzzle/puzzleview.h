#ifndef PUZZLEVIEW_H
#define PUZZLEVIEW_H

#include <QGridLayout>
#include <QObject>
#include <QGridLayout>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QMessageBox>
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
    bool checkSolved();
    QVector<Tile*> get_buttons();
    void genInit();
    void removeWidgetAt(int row, int column);
    long long get_count_of_attempts();
private:
    QGridLayout* _grid;
    QGraphicsView* _view;
    QVector<Tile*> _buttons;
    long long count_of_attempts = 0;
};

#endif // PUZZLEVIEW_H
