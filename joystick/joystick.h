#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QtPlugin>
#include <QObject>
#include <QVector>
class Joystick : public QObject
{
    Q_OBJECT
public:
     virtual QVector<int> getAxes() = 0;
     virtual QVector<int> getButtons() = 0;
     virtual bool isConnected() = 0;
     virtual bool reConnect() = 0;
     virtual int getAxisMaxValue() = 0;
     virtual int getAxisMinValue() = 0;
     virtual ~Joystick(){}
signals :
     void axesMoved();
     void buttonsChanged();
};


Q_DECLARE_INTERFACE(Joystick, "SDLJoystick")


#endif // JOYSTICK_H
