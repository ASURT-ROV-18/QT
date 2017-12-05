#include "mainwindow.h"
#include <QApplication>
#include "network/udpconnection.h"
#include "network/networkhandler.h"
#include "network/tcpconnection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
