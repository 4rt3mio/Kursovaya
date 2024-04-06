#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete puzzleWidget;
}

void MainWindow::on_bnt_select15_clicked()
{
    hide();
    puzzleWidget = new Puzzle15(4);
    puzzleWidget->show();
}

void MainWindow::on_bnt_select8_clicked()
{
    hide();
    puzzleWidget = new Puzzle15(3);
    puzzleWidget->show();
}


void MainWindow::on_bnt_select24_clicked()
{
    hide();
    puzzleWidget = new Puzzle15(5);
    puzzleWidget->show();
}


void MainWindow::on_bnt_select35_clicked()
{
    hide();
    puzzleWidget = new Puzzle15(6);
    puzzleWidget->show();
}
