#ifndef PUZZLE15_H
#define PUZZLE15_H

#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QApplication>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include "tile.h"

namespace Ui {
class Puzzle15;
}

class Puzzle15 : public QWidget
{
    Q_OBJECT

public:
    explicit Puzzle15(QWidget *parent = nullptr);
    ~Puzzle15();
    void moveTile(Tile* tile, int row, int column);
    void showEvent(QShowEvent *event);

private:
    Ui::Puzzle15 *ui;
    QGridLayout* _grid;
    QVector<Tile*> _buttons;
};

#endif // PUZZLE15_H
