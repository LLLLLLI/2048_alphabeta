#include <QApplication>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow *view = new MainWindow;
    view->show();
    return app.exec();
}
