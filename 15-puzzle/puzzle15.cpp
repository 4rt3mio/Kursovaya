#include "puzzle15.h"
#include "ui_puzzle15.h"

Puzzle15::Puzzle15(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Puzzle15)
{
    ui->setupUi(this);
    _grid = new QGridLayout(ui->graphicsView);
    pv = new PuzzleView();
    pv->SetPuzzleView(_grid, ui->graphicsView);
    pv->generateInitialPuzzle();
    pv->genInit();
    _buttons = pv->get_buttons();
    timer = new QTimer;
    QObject::connect(timer, &QTimer::timeout, [=](){
        update();
        ui->lbl_count_attempts->setText(QString::number(pv->get_count_of_attempts()));
    });
    timer->start(25);
}

Puzzle15::~Puzzle15()
{
    delete ui;
}

void Puzzle15::on_bnt_generation_clicked()
{
    pv->generateInitialPuzzle();
    pv->genInit();
    _buttons = pv->get_buttons();
}

