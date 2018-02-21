#include "handlersthread.h"

#include "network/udpconnection.h"
#include "network/networkhandler.h"
#include "network/tcpconnection.h"
#include "joystick/sdljoystick.h"
#include "joystick/joystickhandler.h"

void HandlersThread::run()
{
    qDebug() << "handler Thread" << endl;
    NetworkHandler nh;
    JoystickHandler s(0, &nh);
}

HandlersThread::HandlersThread()
{

}
