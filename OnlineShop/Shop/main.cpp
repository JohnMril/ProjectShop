#include "MainWindow.hpp"
#include "WaitingDialog.hpp"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
//    QThread* main = new QThread();
//    QThread* timer = new QThread();
    MainWindow* w =  new MainWindow();
//    w->moveToThread(main);
//    WaitingDialog* waiter = new WaitingDialog();
//    waiter->moveToThread(timer);
//    main->start();
//    timer->start();
    w->show();
//    waiter->show();
//    waiter->StartTimer();
    return a.exec();
}
