#ifndef PUZZLE15_H
#define PUZZLE15_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
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

private slots:
    void on_bnt_generation_clicked();

    void on_bnt_get_my_result_clicked();

private:
    Ui::Puzzle15 *ui;
    QGridLayout* _grid;
    QVector<Tile*> _buttons;
    PuzzleView *pv;
    QTimer *timer;
};

#endif // PUZZLE15_H
