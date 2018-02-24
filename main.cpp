#include "mainwindow.h"
#include <QApplication>
#include "network/udpconnection.h"
#include "network/networkhandler.h"
#include "network/tcpconnection.h"
#include "joystick/sdljoystick.h"
#include "joystick/joystickhandler.h"
#include <QGst/Init>
#include "handlersthread.h"
#include <QThreadPool>

int main(int argc, char *argv[])
{
    QGst::init(&argc, &argv);
    QApplication a(argc, argv);

//    Camera player1(0, "v4l2src device=/dev/video0 ! video/x-raw, framerate=30/1,widtb=1280,heigt=720 ! vaapipostproc");
//    Camera player1(0, "v4l2src device=/dev/video1 ! image/jpeg, width=1280, height=720, framerate=60/1 ! rtpjpegpay ! application/x-rtp,media=(string)video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc");

    Camera player1(0, "udpsrc port=1234 ! application/x-rtp,media=video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink");
    Camera player2(0, "udpsrc port=5678 ! application/x-rtp,media=video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc");

    player1.init();
    player2.init();
    player1.play();
    player2.play();

    Camera player3(0, "udpsrc port=4321 ! application/x-rtp,media=video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc");
    Camera player4(0, "udpsrc port=8765 ! application/x-rtp,media=video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc");

    player3.init();
    player4.init();
    player3.play();
    player4.play();


    MainWindow w0(0, &player1, &player2, true);
    MainWindow w1(0, &player3, &player4, false);

    NetworkHandler nh;
    JoystickHandler s(0, &nh, &w0);

//    HandlersThread ht;

//    ht.start();
//    ht.wait();

//    w.changeTab(2);

    w0.show();
    w1.show();
    return a.exec();
}
