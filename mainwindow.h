#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "gameview.h"
#include <string>

using namespace std;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    QPushButton *peopleButton;
    QPushButton *aiButton;
    QPushButton *trainButton;
    QLabel *scoreLbl;
    QLabel *biggestLbl;
    QLabel *highsocreLbl;
    GameView *game;
    //QWidget *widget;
    string high;

public slots:
    void onscore(int, int);
};


#endif // MAINWINDOW_H_INCLUDED
