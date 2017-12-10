#include "sdljoystick.h"

SDLJoystick::SDLJoystick()
{
    QObject(0);
    init();
    QTimer *updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkSDLEvents()));
    updateTimer->start(timerUpdateMills);
}

int SDLJoystick::getX()
{
    return (axes.size() >= 1)? axes[0] : 0;
}

int SDLJoystick::getY()
{
    return (axes.size() >= 2)? axes[1] : 0;
}

int SDLJoystick::getZ()
{
    return (axes.size() >= 3)? axes[2] : 0;
}

int SDLJoystick::getR()
{
    return (axes.size() >= 4)? axes[3] : 0;
}

QVector<int> *SDLJoystick::getButtons()
{
    return NULL;
}



bool SDLJoystick::init()
{
    if(SDL_Init(SDL_INIT_JOYSTICK ) < 0){
        qDebug() << "failed " << SDL_GetError() << endl;
        return false;
    }

    if(SDL_NumJoysticks() < 1){
        qDebug() << "no Joystick connected" << endl;
        return false;
    }else{
        controller = SDL_JoystickOpen(0);
        if(controller == NULL){
            qDebug() << "Unable to open game controller " << SDL_GetError() << endl;
            return false;
        }else{
            qDebug() << "The Joystick is connected " << endl;
            axes.resize(SDL_JoystickNumAxes(controller));
            buttons.resize(SDL_JoystickNumButtons(controller));
            return true;
        }
    }
}

void SDLJoystick::updateAxes(SDL_Event e)
{
    if(e.jaxis.which != 0) return;
    axes[e.jaxis.axis] = e.jaxis.value;
    qDebug() << "axis "<< e.jaxis.axis << " " << e.jaxis.value << endl;
    emit axesMoved();
}

void SDLJoystick::updateButtons(SDL_Event e)
{
    buttons[e.jbutton.button] = e.jbutton.state;
    qDebug() << "button " << e.jbutton.button << " " << e.jbutton.state;
    emit buttonChanged(e.jbutton.button);
}


void SDLJoystick::checkSDLEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0){
        switch(event.type){
            case SDL_JOYAXISMOTION:
                updateAxes(event);
                break;
            case SDL_JOYBUTTONDOWN:
                updateButtons(event);
                break;
            case SDL_JOYBUTTONUP:
                updateButtons(event);
                break;
        }
    }
}

SDLJoystick::~SDLJoystick()
{
    SDL_JoystickClose(controller);
}
