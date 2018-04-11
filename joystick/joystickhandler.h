#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H
#include "joystick.h"
#include <math.h>
#include <network/networkhandler.h>
#include "mainwindow.h"
#include <QString>
#include <QVector>

class JoystickHandler : public QObject
{
    Q_OBJECT
public:
    JoystickHandler(int libNumber);
    JoystickHandler(int libNumber, NetworkHandler *networkHandler);
    JoystickHandler(int libNumber, NetworkHandler *networkHandler, MainWindow *mainWindow);
    int mode = 0;
    ~JoystickHandler();
    QVector<int> axesLastValues;

private:
    static int AXES_MESSAGE;
    static int BUTTONS_MESSAGE;
    Joystick *joystick = NULL;
    QVector<int> buttonsLastValues;
    QVector<int> compareAxes(QVector<int> newReadings);
    QVector<int> ignoreError(QVector<int> diffs, QVector<int> newReadings);
    void updateAxes(QVector<int> diffs, QVector<int> newReadings);
    void updateButtons(QVector<int> diffs, QVector<int> newReadings);
    QString buildMessage(int messageType, QVector<int> values);
    QString buildMessage_noargs();
    QVector<int> compareButtons(QVector<int> newReadings);
    int ERROR_PERCENTAGE = 0;
    void init(int libNumber);
    int libNumber;
    MainWindow *mainWindow;

public slots:
    void validateNewAxesData();
    void validateNewButtonsData();
    void reconnect();
    void send();

signals:
    void sendJoystickData(QString message);
    void sendJoystickData_noargs(QString message);
    void updateLabels(QVector<int>);

};

#endif // JOYSTICKHANDLER_H
