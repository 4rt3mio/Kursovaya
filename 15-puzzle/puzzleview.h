#ifndef PUZZLEVIEW_H
#define PUZZLEVIEW_H

#include <QGridLayout>
#include <QObject>
#include <QGridLayout>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <random>
#include <algorithm>
#include "tile.h"

class PuzzleView : public QWidget
{
    Q_OBJECT

public:
    explicit PuzzleView(QWidget *parent = nullptr);
    ~PuzzleView();
    void SetPuzzleView(QGridLayout* grid, QGraphicsView* view, long long field_size);
    void generateInitialPuzzle();
    void generateInitialPicturePuzzle();
    void moveTile(Tile* tile, int row, int column);
    bool isMovebleLeft(int index);
    bool isMovebleRight(int index);
    bool isMovebleUp(int index);
    bool isMovebleDown(int index);
    void move(Tile* tile);
    void shuffleTiles();
    bool isSolvable();
    bool checkSolved();
    void appendAttemptsToFile(int count_of_attempts);
    void readResultsFromFile();
    void showBestResults();
    QVector<Tile*> get_buttons();
    void genInit();
    void removeWidgetAt(int row, int column);
    long long get_count_of_attempts();
private:
    QGridLayout* _grid;
    QGraphicsView* _view;
    long long _field_size;
    long long _cnt_tiles;
    QVector<Tile*> _buttons;
    long long count_of_attempts = 0;
    QVector <long long> results;
    bool isPicture = false;
};

#endif // PUZZLEVIEW_H
