#include "puzzle15.h"
#include "ui_puzzle15.h"

Puzzle15::Puzzle15(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Puzzle15)
{
    ui->setupUi(this);
    _grid = new QGridLayout(ui->graphicsView);
    pv = new PuzzleView(_grid, ui->graphicsView);
    pv->generateInitialPuzzle();
    _buttons = pv->get_buttons();
}

Puzzle15::~Puzzle15()
{
    delete ui;
}

void Puzzle15::showEvent(QShowEvent *event)
{
    pv->moveTile(_buttons[1], 3, 3);
    pv->moveTile(_buttons[5], 0, 1);
}
