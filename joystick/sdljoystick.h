#ifndef SDLJOYSTICK_H
#define SDLJOYSTICK_H
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL.h>
#include <exception>
#include <QObject>
#include <QDebug>
#include <QtCore/QObject>
#include <QVector>
#include <QTimer>
#include "joystick.h"

class SDLJoystick : Joystick
{
    Q_OBJECT
    Q_INTERFACES(Joystick)
public:
    SDLJoystick();
    int getX();
    int getY();
    int getZ();
    int getR();
    QVector<int>* getButtons();
    ~SDLJoystick();
private:
    bool init();
    SDL_Joystick *controller = NULL;
    QVector<int> axes;
    QVector<int> buttons;
    const int timerUpdateMills = 100;
    void updateAxes(SDL_Event e);
    void updateButtons(SDL_Event e);
private slots:
    void checkSDLEvents();

signals:
};

#endif // SDLJOYSTICK_H
