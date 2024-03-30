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

private slots:
    void on_bnt_select15_clicked();

private:
    Ui::MainWindow *ui;
    Puzzle15 puzzleWidget;
};
#endif // MAINWINDOW_H
