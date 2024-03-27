#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QGridLayout>
#include <QPropertyAnimation>
#include "tile.h"
#include "puzzle15.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void moveTile(Tile* tile, int row, int column);
    void showEvent(QShowEvent *event);

private:
    Ui::MainWindow *ui;
    Puzzle15 puzzleWidget;
    QGridLayout* _grid;
    QVector<Tile*> _buttons;
};
#endif // MAINWINDOW_H
