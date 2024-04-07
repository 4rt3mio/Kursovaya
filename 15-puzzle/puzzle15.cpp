#include "puzzle15.h"
#include "ui_puzzle15.h"

Puzzle15::Puzzle15(int size, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Puzzle15)
{
    ui->setupUi(this);
    client = new Client_Part;
    connect(client, &Client_Part::dataReady, this, &Puzzle15::handleServerResponse);
    ui->graphicsView->setStyleSheet("background-color: #eb86dd;");
    _grid = new QGridLayout(ui->graphicsView);
    pv = new PuzzleView();
    pv->SetPuzzleView(_grid, ui->graphicsView, size);
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

void Puzzle15::on_bnt_connect_to_server_clicked()
{
    dataInput = new DataInput;
    dataInput->setWindowModality(Qt::ApplicationModal);
    dataInput->show();
    connect(dataInput, &DataInput::formClosed, [=](const QString& name, const QString& IP, const QString& port) {
        client->connectToServer(IP, port.toInt());
        nickname = name;
        pv->setClient(client, nickname);
    });
}

void Puzzle15::on_bnt_servr_result_clicked()
{
    if (client->isConnected()) client->send_results("send_map_request");
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

    QList<QPair<QString, QVector<int>>> results;

    for (const QString& line : lines) {
        int openBraceIndex = line.indexOf('{');
        int closeBraceIndex = line.indexOf('}');

        if (openBraceIndex == -1 || closeBraceIndex == -1)
            continue;

        QString nick = line.left(openBraceIndex - 3).trimmed();

        QString scoresStr = line.mid(openBraceIndex + 1, closeBraceIndex - openBraceIndex - 1);

        QStringList scoresList = scoresStr.split(", ");
        QVector<int> scores;
        for (const QString& score : scoresList) {
            scores.append(score.toInt());
        }

        results.append(qMakePair(nick, scores));
    }

    std::sort(results.begin(), results.end(), [](const QPair<QString, QVector<int>>& a, const QPair<QString, QVector<int>>& b) {
        int sumA = std::accumulate(a.second.begin(), a.second.end(), 0);
        int sumB = std::accumulate(b.second.begin(), b.second.end(), 0);
        return sumA > sumB;
    });

    results = results.mid(0, 15);

    QString message;
    for (int i = 0; i < results.size(); ++i) {
        QString nick = results[i].first;
        QVector<int> scores = results[i].second;

        QString scoresStr;
        for (int j = 0; j < scores.size(); ++j) {
            scoresStr += QString::number(scores[j]);
            if (j < scores.size() - 1)
                scoresStr += ", ";
        }

        message += QString("%1) %2 - {%3}\n").arg(i + 1).arg(nick).arg(scoresStr);
    }
    if (!message.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.resize(600, 600);
        msgBox.exec();
    }
}
