#include "puzzleview.h"

PuzzleView::PuzzleView(QGridLayout* grid, QGraphicsView* view)
{
    _grid = grid;
    _view = view;
}

void PuzzleView::generateInitialPuzzle()
{
    _buttons.clear();
    int cellSize = std::min(_view->width(), _view->height()) / 4;

    for (int i = 0; i < 16; i++) {
        auto new_btn = new Tile(_view);
        new_btn->set_index(i);
        int tileSize = cellSize - 10;
        new_btn->setMinimumSize(tileSize, tileSize);
        _grid->addWidget(new_btn, i / 4, i % 4);
        //connect(new_btn, &Tile::fifteen_btn_clicked, this, &PuzzleView::move);
        _buttons.append(new_btn);
    }
    for (int i = 0; i < 16; i++) {
        _buttons[i]->set_number(i);
        if (i == 0) {
            _buttons[i]->setVisible(false);
            _buttons[i]->setEnabled(false);
        }
    }
    shuffleTiles();
    _view->setLayout(_grid);
}

void PuzzleView::shuffleTiles()
{
    QVector<int> indices(16);
    std::iota(indices.begin(), indices.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);
    for (int i = 0; i < 16; ++i) {
        int newIndex = indices[i];
        _buttons[newIndex]->set_index(i);
        int row = i / 4;
        int column = i % 4;
        _grid->addWidget(_buttons[newIndex], row, column);
    }
}

bool PuzzleView::isSolvable()
{
    int inv = 0;
    for (int i = 0; i < 16; ++i)
    {
        int currentIndex = _buttons[i]->get_index();
        if (currentIndex)
        {
            for (int j = 0; j < i; ++j)
            {
                int comparedIndex = _buttons[j]->get_index();
                if (comparedIndex > currentIndex)
                {
                    ++inv;
                }
            }
        }
    }
    for (int i = 0; i < 16; ++i)
    {
        if (_buttons[i]->get_index() == 0)
        {
            inv += 1 + i / 4;
        }
    }
    return (inv % 2 == 0);
}

QVector<Tile *> PuzzleView::get_buttons()
{
    return _buttons;
}

void PuzzleView::genInit()
{
    shuffleTiles();
    if (!isSolvable()) {
        if (_buttons[0]->get_index() != 0 && _buttons[1]->get_index() != 0) {
            _grid->addWidget(_buttons[0], 0, 1);
            _grid->addWidget(_buttons[1], 0, 0);
            _buttons[0]->set_index(1);
            _buttons[1]->set_index(0);
        }
        else if (_buttons[1]->get_index() != 0 && _buttons[2]->get_index() != 0) {
            _grid->addWidget(_buttons[1], 0, 2);
            _grid->addWidget(_buttons[2], 0, 1);
            _buttons[1]->set_index(2);
            _buttons[2]->set_index(1);
        }
        else {
            _grid->addWidget(_buttons[2], 0, 3);
            _grid->addWidget(_buttons[3], 0, 2);
            _buttons[2]->set_index(3);
            _buttons[3]->set_index(2);
        }
    }
}

void PuzzleView::moveTile(Tile *tile, int row, int column)
{
    QPropertyAnimation *animation = new QPropertyAnimation(tile, "geometry", nullptr);

    int startX = tile->x();
    int startY = tile->y();

    int ind = row * 4 + column;
    Tile* end_button;
    for (int i = 0; i < _buttons.size(); ++i) {
        if (_buttons[i]->get_index() == ind) {
            end_button = _buttons[i];
        }
    }
    int endX = end_button->x();
    int endY = end_button->y();
    animation->setDuration(2000);
    animation->setStartValue(QRect(startX, startY, tile->width(), tile->height()));
    animation->setEndValue(QRect(endX, endY, tile->width(), tile->height()));
    animation->start();
}

bool PuzzleView::isMoved(int index)
{
    //
}

void PuzzleView::move(int _ind)
{

}
