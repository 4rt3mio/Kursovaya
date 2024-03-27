#include "tile.h"

Tile::Tile(QWidget *parent)
    : QPushButton(parent) {}

void Tile::set_number(short number)
{
    _number = number;
    setText(QString::number(_number));
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
