#include <QtGui>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //widget = new QWidget(this);
    //widget->setGeometry(0, 0, 460, 640)
    //widget->setBackgroundBrush(QColor("#b8af9e"));

    game = new GameView(this);
    game->setGeometry(0, 100, 460, 460);
    connect(game, SIGNAL(scoreupdata(int, int)), this, SLOT(onscore(int, int)));
    //connect(game, SIGNAL(ai_done()), game, SLOT(ai_play()));

    QFont font;
    font.setFamily("Consolas");
    font.setBold(false);
    font.setPixelSize(30);

    peopleButton = new QPushButton("Play", this);
    peopleButton->setGeometry(10, 580, 130, 50);
    peopleButton->setFont(font);
    connect(peopleButton, SIGNAL(clicked()), game, SLOT(restartGame()));

    aiButton = new QPushButton("show", this);
    aiButton->setGeometry(170, 580, 130, 50);
    aiButton->setFont(font);
    connect(aiButton, SIGNAL(clicked()), game, SLOT(ai_play()));

    trainButton = new QPushButton("better", this);
    trainButton->setGeometry(320, 580, 130, 50);
    trainButton->setFont(font);
    connect(trainButton, SIGNAL(clicked()), game, SLOT(train()));

    highsocreLbl = new QLabel(QString("High Score:\n%1").arg(game->getHigh()), this);
    highsocreLbl->setGeometry(0, 0, 200, 100);
    highsocreLbl->setFont(font);
    highsocreLbl->setAlignment(Qt::AlignCenter);

    scoreLbl = new QLabel(QString("Score:%1").arg(game->getScore()), this);
    scoreLbl->setGeometry(210, 0, 200, 40);
    scoreLbl->setFont(font);
    scoreLbl->setAlignment(Qt::AlignCenter);

    biggestLbl = new QLabel(QString("Compound:%1").arg(game->getBiggest()), this);
    biggestLbl->setGeometry(210, 45, 200, 40);
    biggestLbl->setFont(font);
    biggestLbl->setAlignment(Qt::AlignCenter);
}

void MainWindow::onscore(int score, int big)
{
    scoreLbl->setText(QString("Score:%1").arg(score));
    biggestLbl->setText(QString("Compound:%1").arg(big));
    if (score > game->getHigh())
    {
        highsocreLbl->setText(QString("High Score:\n%1").arg(score));
    }
}
