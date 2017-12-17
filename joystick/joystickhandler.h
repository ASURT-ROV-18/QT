#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H
#include "joystick.h"

class JoystickHandler : public QObject
{
    Q_OBJECT
public:
    JoystickHandler(int libNumber);
private:
    static int AXES_MESSAGE;
    static int BUTTONS_MESSAGE;
    Joystick *joystick;
    QVector<int> axesLastValues;
    QVector<int> buttonsLastValues;
    QVector<int> compareAxies(QVector<int> newReadings);
    QVector<int> ignoreError(QVector<int> diffs, QVector<int> newReadings);
    int ERROR_PERCENTAGE = 5;
    void updateAxes(QVector<int> diffs, QVector<int> newReadings);
    void updateButtons(QVector<int> diffs, QVector<int> newReadings);
    QString buildMessage(int messageType, QVector<int> values);
    QVector<int> compareButtons(QVector<int> newReadings);

public slots:
    void validateNewAxesData();
    void validateNewButtonsData();
signals:
    void sendJoystickData(QString message);
};

#endif // JOYSTICKHANDLER_H
