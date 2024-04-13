#include "puzzle15.h"
#include "ui_puzzle15.h"


Puzzle15::Puzzle15(int size, QMainWindow *mainWindow, Client_Part *client, QString nick, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Puzzle15)
{
    ui->setupUi(this);
    _mainWindow = mainWindow;
    _fieldSize = size;
    _client = client;
    nickname = nick;
    connect(_client, &Client_Part::dataReady, this, &Puzzle15::handleServerResponse);
    ui->graphicsView->setStyleSheet("background-color: #eb86dd;");
    _grid = new QGridLayout(ui->graphicsView);
    pv = new PuzzleView();
    pv->SetPuzzleView(_grid, ui->graphicsView, size);
    pv->generateInitialPuzzle();
    pv->genInit();
    pv->setClient(_client, nickname);
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
    if (ui->cbx_picture->isChecked()) pv->generateInitialPicturePuzzle();
    else pv->generateInitialPuzzle();
    pv->genInit();
    _buttons = pv->get_buttons();
}


void Puzzle15::on_bnt_get_my_result_clicked()
{
    pv->readResultsFromFile();
    pv->showBestResults();
}

void Puzzle15::on_bnt_servr_result_clicked()
{
    if (_client->isConnected()) _client->send_results(QString::number(_fieldSize) + "send_map_request");
    else {
        QString message = "Вы еще не подключились к серверу!!!";
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setFixedSize(1600, 1600);
        msgBox.move(QGuiApplication::primaryScreen()->geometry().center() - msgBox.rect().center());
        msgBox.exec();
    }
}

bool compareSecond(const QPair<QString, int> &pair1, const QPair<QString, int> &pair2)
{
    return pair1.second < pair2.second;
}

void Puzzle15::handleServerResponse(const QByteArray &data)
{
    QString response = QString::fromUtf8(data);
    if (response == "Welcome to this Server") {
        QString message = "Вы присоеденились к серверу!!!";
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.resize(600, 600);
        msgBox.exec();
    }

    QStringList lines = response.split("\n");

    QVector<QPair<QString, int>> results;

    for (const QString& line : lines) {
        int openBraceIndex = line.indexOf('{');
        int closeBraceIndex = line.indexOf('}');

        if (openBraceIndex == -1 || closeBraceIndex == -1)
            continue;

        QString nick = line.left(openBraceIndex - 3).trimmed();

        QString scoresStr = line.mid(openBraceIndex + 1, closeBraceIndex - openBraceIndex - 1);

        QStringList scoresList = scoresStr.split(", ");
        for (const QString& score : scoresList) {
            results.push_back(qMakePair(nick, score.toInt()));
        }
    }

    std::sort(results.begin(), results.end(), compareSecond);

    results = results.mid(0, 15);

    QString message = "<html><body><h2>Текущее положение на сервере:</h2><ol>";
    for (int i = 0; i < results.size(); ++i) {
        QString nick = results[i].first;
        int score = results[i].second;
        message += "<li><b>" + nick + "</b> - " + QString::number(score) + " очков</li>";
    }
    message += "</ol></body></html>";
    QMessageBox::information(nullptr, "Текущее положение на сервере", message);
}

void Puzzle15::on_bnt_goBackToMainMenu_clicked()
{
    hide();
    disconnect(_client, &Client_Part::dataReady, this, &Puzzle15::handleServerResponse);
    _mainWindow->show();
}


void Puzzle15::on_bnt_close_clicked()
{
    close();
}

