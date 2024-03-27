#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    _grid = new QGridLayout(centralWidget);
    for (int i = 0; i < 16; i++) {
        auto new_btn = new Tile(centralWidget);
        new_btn->set_index(i);
        new_btn->setMinimumSize(200, 200);
        _grid->addWidget(new_btn, i / 4, i % 4);
        _buttons.append(new_btn);
    }
    for (int i = 0; i < 16; i++) {
        _buttons[i]->set_number(i);
    }
    centralWidget->setLayout(_grid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveTile(Tile *tile, int row, int column)
{
    QPropertyAnimation *animation = new QPropertyAnimation(tile, "geometry", this);

    // Вычисляем новое положение плитки в сетке
    int x = _grid->cellRect(row, column).x();
    int y = _grid->cellRect(row, column).y();

    // Задаем параметры анимации
    animation->setDuration(2000); // Продолжительность анимации в миллисекундах
    animation->setStartValue(tile->geometry()); // Начальное положение плитки
    animation->setEndValue(QRect(x, y, tile->width(), tile->height())); // Конечное положение плитки
    connect(animation, &QPropertyAnimation::finished, [=]() {
        _grid->removeWidget(tile); // Удаляем плитку из текущей позиции в QGridLayout
        _grid->addWidget(tile, row, column); // Добавляем плитку на новую позицию в QGridLayout
    });
    animation->start();
}

void MainWindow::showEvent(QShowEvent *event)
{
    puzzleWidget.show();
    QMainWindow::showEvent(event);
    moveTile(_buttons[1], 1, 1);
    moveTile(_buttons[5], 0, 1);
}
