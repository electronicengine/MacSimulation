#include "mainwindow.h"
#include <QtGlobal>
#include <QTime>
#include "logging.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(0));

    Logging::disableLogs();

    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    w->show();

    return a.exec();
}
