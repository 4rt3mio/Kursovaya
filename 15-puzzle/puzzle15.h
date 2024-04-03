#ifndef PUZZLE15_H
#define PUZZLE15_H

#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QApplication>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <random>
#include "tile.h"
#include "puzzleview.h"

namespace Ui {
class Puzzle15;
}

class Puzzle15 : public QWidget
{
    Q_OBJECT

public:
    explicit Puzzle15(QWidget *parent = nullptr);
    ~Puzzle15();
    void showEvent(QShowEvent *event);

private:
    Ui::Puzzle15 *ui;
    QGridLayout* _grid;
    QVector<Tile*> _buttons;
    PuzzleView *pv;
};

#endif // PUZZLE15_H
