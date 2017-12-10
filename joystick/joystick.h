#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QtPlugin>
#include <QObject>
#include <QVector>
class Joystick : public QObject
{
    Q_OBJECT
public:
     virtual int getX() = 0;
     virtual int getY() = 0;
     virtual int getZ() = 0;
     virtual int getR() = 0;
     virtual QVector<int>* getButtons() = 0;
     virtual ~Joystick(){}
signals :
     void axesMoved();
     void buttonChanged(int);
};


Q_DECLARE_INTERFACE(Joystick, "SDLJoystick")


#endif // JOYSTICK_H
