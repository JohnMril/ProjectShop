#include "MainWindow.hpp"
#include "WaitingDialog.hpp"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
//    QThread main;
//    QThread timer;
    MainWindow w;
//    w.moveToThread(&main);
//    WaitingDialog waiter;
//    waiter.moveToThread(&timer);

    w.show();
//    waiter.StartTimer();
    return a.exec();
}
