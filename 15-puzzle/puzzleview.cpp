#include "puzzleview.h"

PuzzleView::PuzzleView(QGridLayout* grid, QGraphicsView* view)
{
    _grid = grid;
    _view = view;
}

void PuzzleView::generateInitialPuzzle()
{
    QLayoutItem *child;
    while ((child = _grid->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    _buttons.clear();
    int cellSize = std::min(_view->width(), _view->height()) / 4;

    for (int i = 0; i < 16; i++) {
        auto new_btn = new Tile(_view);
        new_btn->set_index(i);
        int tileSize = cellSize - 10;
        new_btn->setMinimumSize(tileSize, tileSize);
        _grid->addWidget(new_btn, i / 4, i % 4);
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

    int startX = _grid->itemAtPosition(tile->get_index() / 4, tile->get_index() % 4)->geometry().x();
    int startY = _grid->itemAtPosition(tile->get_index() / 4, tile->get_index() % 4)->geometry().y();

    QRect endRect = _grid->cellRect(row, column);

    int endX = endRect.x();
    int endY = endRect.y();

    animation->setDuration(1000);
    animation->setStartValue(QRect(startX, startY, tile->width(), tile->height()));
    animation->setEndValue(QRect(endX, endY, tile->width(), tile->height()));

    _grid->addWidget(tile, row, column);
    /*registerAnimationFinishedCallback([=]() {
        _grid->addWidget(tile, row, column);
    });*/

    animation->start();
}

bool PuzzleView::isMovebleLeft(int index)
{
    if (index % 4 != 0) {
        int find_index = index - 1;
        for (Tile *button : _buttons) {
            if (button->get_index() == find_index) {
                if (button->get_number() == 0) {
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

bool PuzzleView::isMovebleRight(int index)
{
    if (index % 4 != 3) {
        int find_index = index + 1;
        for (Tile *button : _buttons) {
            if (button->get_index() == find_index) {
                if (button->get_number() == 0) {
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

bool PuzzleView::isMovebleUp(int index)
{
    if (index > 3) {
        int find_index = index - 4;
        for (Tile *button : _buttons) {
            if (button->get_index() == find_index) {
                if (button->get_number() == 0) {
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

bool PuzzleView::isMovebleDown(int index)
{
    if (index < 12) {
        int find_index = index + 4;
        for (Tile *button : _buttons) {
            if (button->get_index() == find_index) {
                if (button->get_number() == 0) {
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

/*void PuzzleView::registerAnimationFinishedCallback(std::function<void ()> callback)
{
    _animationFinishedCallback = callback;
}*/

void PuzzleView::move(Tile *tile)
{
    int tile_index = tile->get_index();
    Tile *null_tile;
    if (isMovebleLeft(tile_index)) {
        int find_index = tile_index - 1;
        for (Tile *button : _buttons) {
            if (button->get_index() == find_index) {
                null_tile = button;
            }
        }
        int column = tile_index % 4;
        int row = tile_index / 4;
        moveTile(tile, row, column - 1);
        moveTile(null_tile, row, column);
        null_tile->set_index(tile_index);
        tile->set_index(tile_index - 1);
    }
    else if (isMovebleRight(tile_index)) {
        int find_index = tile_index + 1;
        for (Tile *button : _buttons) {
            if (button->get_index() == find_index) {
                null_tile = button;
            }
        }
        int column = tile_index % 4;
        int row = tile_index / 4;
        moveTile(tile, row, column + 1);
        moveTile(null_tile, row, column);
        null_tile->set_index(tile_index);
        tile->set_index(tile_index + 1);
    }
    else if (isMovebleUp(tile_index)) {

    }
    else if (isMovebleDown(tile_index)) {

    }
}
