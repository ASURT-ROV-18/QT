#include "mainwindow.h"
#include <QApplication>
#include "network/udpconnection.h"
#include "network/networkhandler.h"
#include "network/tcpconnection.h"
#include "joystick/sdljoystick.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SDLJoystick s;
    w.show();
    return a.exec();
}
