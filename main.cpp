#include "mainwindow.h"
#include <QApplication>
#include "network/udpconnection.h"
#include "network/networkhandler.h"
#include "network/tcpconnection.h"
#include "joystick/sdljoystick.h"
#include "joystick/joystickhandler.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    NetworkHandler nh;
    JoystickHandler s(0, &nh);
    w.show();
    return a.exec();
}
