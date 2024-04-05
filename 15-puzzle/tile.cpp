#include "tile.h"

Tile::Tile(QWidget *parent)
    : QPushButton(parent) {
    int red = QRandomGenerator::global()->bounded(256);
    int green = QRandomGenerator::global()->bounded(256);
    int blue = QRandomGenerator::global()->bounded(256);
    QString colorStyle = QString("background-color: rgb(%1, %2, %3);").arg(red).arg(green).arg(blue);
    setStyleSheet(QString("QPushButton {%1}").arg(colorStyle));
}

void Tile::set_number(short number)
{
    _number = number;
    setText(QString::number(_number));
    QFont font = this->font();
    font.setBold(true);
    font.setPointSize(16);
    setFont(font);
}

void Tile::set_index(short index)
{
    _ind = index;
}

short Tile::get_number()
{
    return _number;
}

short Tile::get_index()
{
    return _ind;
}
