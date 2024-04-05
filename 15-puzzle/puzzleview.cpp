#include "puzzleview.h"

PuzzleView::PuzzleView(QWidget *parent)
    : QWidget(parent) {
    //я пидор
}

PuzzleView::~PuzzleView()
{
    for (Tile *tile : _buttons) {
        delete tile;
    }
    _buttons.clear();
}

void PuzzleView::SetPuzzleView(QGridLayout* grid, QGraphicsView* view)
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
    count_of_attempts = 0;
    int cellSize = std::min(_view->width(), _view->height()) / 4;

    for (int i = 0; i < 16; i++) {
        auto new_btn = new Tile(_view);
        new_btn->set_index(i);
        int tileSize = cellSize - 10;
        new_btn->setMinimumSize(tileSize, tileSize);
        _grid->addWidget(new_btn, i / 4, i % 4);
        connect(new_btn, &Tile::clicked, this, [this, new_btn]() {
            move(new_btn);
        });
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
    QVector<short> vec_for_check(16);
    for (Tile *button : _buttons) {
        vec_for_check[button->get_index()] = button->get_number();
    }

    int inv = 0;
    for (int i = 0; i < 16; ++i)
    {
        if (vec_for_check[i] != 0)
        {
            for (int j = 0; j < i; ++j)
            {
                if (vec_for_check[j] != 0 && vec_for_check[j] > vec_for_check[i])
                {
                    ++inv;
                }
            }
        }
    }

    for (int i = 0; i < 16; ++i)
    {
        if (vec_for_check[i] == 0)
        {
            inv += 1 + i / 4;
        }
    }

    return (inv % 2 == 0);
}

bool PuzzleView::checkSolved()
{
    for (Tile *button : _buttons) {
        if (button->get_number() == 0) {
            if (button->get_index() != 15) return false;
        }
        else if (button->get_index() != (button->get_number() - 1)) return false;
    }
    return true;
}

QVector<Tile *> PuzzleView::get_buttons()
{
    return _buttons;
}

void PuzzleView::genInit()
{
    shuffleTiles();
    while (!isSolvable()) {
        shuffleTiles();
    }
}

void PuzzleView::removeWidgetAt(int row, int column)
{
    QWidget *widgetToRemove = _grid->itemAtPosition(row, column)->widget();
    if (widgetToRemove) {
        _grid->removeWidget(widgetToRemove);
        delete widgetToRemove;
    }
}

long long PuzzleView::get_count_of_attempts()
{
    return count_of_attempts;
}

void PuzzleView::moveTile(Tile *tile, int row, int column)
{
    QPropertyAnimation *animation = new QPropertyAnimation(tile, "geometry", nullptr);
    for (Tile *button : _buttons) {
        button->setEnabled(false);
    }

    int startX = _grid->itemAtPosition(tile->get_index() / 4, tile->get_index() % 4)->geometry().x();
    int startY = _grid->itemAtPosition(tile->get_index() / 4, tile->get_index() % 4)->geometry().y();

    QRect endRect = _grid->cellRect(row, column);

    int endX = endRect.x();
    int endY = endRect.y();

    animation->setDuration(150);
    animation->setStartValue(QRect(startX, startY, tile->width(), tile->height()));
    animation->setEndValue(QRect(endX, endY, tile->width(), tile->height()));

    connect(animation, &QPropertyAnimation::finished, [=]() {
        _grid->addWidget(tile, row, column);
        for (Tile *button : _buttons) {
            button->setEnabled(true);
        }
        animation->deleteLater();
    });

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
        count_of_attempts++;
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
        count_of_attempts++;
    }
    else if (isMovebleUp(tile_index)) {
        int find_index = tile_index - 4;
        for (Tile *button : _buttons) {
            if (button->get_index() == find_index) {
                null_tile = button;
            }
        }
        int column = tile_index % 4;
        int row = tile_index / 4;
        moveTile(tile, row - 1, column);
        moveTile(null_tile, row, column);
        null_tile->set_index(tile_index);
        tile->set_index(tile_index - 4);
        count_of_attempts++;
    }
    else if (isMovebleDown(tile_index)) {
        int find_index = tile_index + 4;
        for (Tile *button : _buttons) {
            if (button->get_index() == find_index) {
                null_tile = button;
            }
        }
        int column = tile_index % 4;
        int row = tile_index / 4;
        moveTile(tile, row + 1, column);
        moveTile(null_tile, row, column);
        null_tile->set_index(tile_index);
        tile->set_index(tile_index + 4);
        count_of_attempts++;
    }
    if (checkSolved()) {
        QMessageBox msgBox;
        const QString message = "<html><body>"
                                "<h1>Головоломка собрана!</h1>"
                                "<p>Количество ходов: </p>" + QString::number(count_of_attempts) +
                                "<p>Запускаем новую игру!!!</p>"
                                "</body></html>";
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.resize(600, 600);
        msgBox.adjustSize();
        QAbstractButton *okButton = msgBox.addButton(tr("OK"), QMessageBox::ActionRole);
        QObject::connect(okButton, &QAbstractButton::clicked, [=]() {
            generateInitialPuzzle();
            genInit();
        });
        QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
        int x = (screenGeometry.width() - msgBox.width()) / 2;
        int y = (screenGeometry.height() - msgBox.height()) / 2;
        msgBox.move(x, y);
        msgBox.exec();
    }
}
