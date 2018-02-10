#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H
#include "joystick.h"
#include <math.h>
#include <network/networkhandler.h>

class JoystickHandler : public QObject
{
    Q_OBJECT
public:
    JoystickHandler(int libNumber);
    JoystickHandler(int libNumber, NetworkHandler *networkHandler);
private:
    static int AXES_MESSAGE;
    static int BUTTONS_MESSAGE;
    Joystick *joystick = NULL;
    QVector<int> axesLastValues;
    QVector<int> buttonsLastValues;
    QVector<int> compareAxes(QVector<int> newReadings);
    QVector<int> ignoreError(QVector<int> diffs, QVector<int> newReadings);
    void updateAxes(QVector<int> diffs, QVector<int> newReadings);
    void updateButtons(QVector<int> diffs, QVector<int> newReadings);
    QString buildMessage(int messageType, QVector<int> values);
    QVector<int> compareButtons(QVector<int> newReadings);
    int ERROR_PERCENTAGE = 0;
    void init(int libNumber);
    int libNumber;

public slots:
    void validateNewAxesData();
    void validateNewButtonsData();
    void reconnect();

signals:
    void sendJoystickData(QString message);
};

#endif // JOYSTICKHANDLER_H
