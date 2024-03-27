#include "puzzle15.h"
#include "ui_puzzle15.h"

Puzzle15::Puzzle15(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Puzzle15)
{
    ui->setupUi(this);
    _grid = new QGridLayout(ui->graphicsView);

    // Получаем размеры ячейки сетки
    int cellSize = std::min(ui->graphicsView->width(), ui->graphicsView->height()) / 4; // Предполагаем, что размеры сетки определяются размерами QGraphicsView

    for (int i = 0; i < 16; i++) {
        auto new_btn = new Tile(ui->graphicsView);
        new_btn->set_index(i);
        // Устанавливаем размер плитки чуть меньше размера ячейки
        int tileSize = cellSize - 10; // На 10 пикселей меньше
        new_btn->setMinimumSize(tileSize, tileSize);

        _grid->addWidget(new_btn, i / 4, i % 4);
        _buttons.append(new_btn);
    }
    for (int i = 0; i < 16; i++) {
        _buttons[i]->set_number(i);
    }
    ui->graphicsView->setLayout(_grid);
}


Puzzle15::~Puzzle15()
{
    delete ui;
}

void Puzzle15::moveTile(Tile *tile, int row, int column)
{
    QPropertyAnimation *animation = new QPropertyAnimation(tile, "geometry", this);

    // Получаем размеры ячейки сетки
    int cellSize = std::min(ui->graphicsView->width(), ui->graphicsView->height()) / 4; // Предполагаем, что размеры сетки определяются размерами QGraphicsView

    // Вычисляем начальное положение плитки в сетке
    int startX = tile->x();
    int startY = tile->y();

    int ind = row * 4 + column;
    Tile* end_button = _buttons[ind];
    // Вычисляем конечное положение плитки в сетке
    int endX = end_button->x();
    int endY = end_button->y();

    // Задаем параметры анимации
    animation->setDuration(2000); // Продолжительность анимации в миллисекундах
    animation->setStartValue(QRect(startX, startY, tile->width(), tile->height())); // Начальное положение плитки
    animation->setEndValue(QRect(endX, endY, tile->width(), tile->height())); // Конечное положение плитки
    connect(animation, &QPropertyAnimation::finished, [=]() {
        _grid->removeWidget(tile); // Удаляем плитку из текущей позиции в QGridLayout
        _grid->addWidget(tile, row, column); // Добавляем плитку на новую позицию в QGridLayout
    });
    animation->start();
}



void Puzzle15::showEvent(QShowEvent *event)
{
    moveTile(_buttons[1], 1, 1);
    moveTile(_buttons[5], 0, 1);
}
