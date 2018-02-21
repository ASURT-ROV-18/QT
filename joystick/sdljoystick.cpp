#include "sdljoystick.h"

int SDLJoystick::SDLLIB = 0;
SDLJoystick::SDLJoystick()
{
    QObject(0);
    connected = init();
    QTimer *updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkSDLEvents()));
    updateTimer->start(timerUpdateMills);
}

QVector<int> SDLJoystick::getAxes()
{
    return axes;
}

QVector<int> SDLJoystick::getButtons()
{
    return buttons;
}

bool SDLJoystick::isConnected()
{
    return init();
}

bool SDLJoystick::reConnect()
{
   return init();
}

int SDLJoystick::getAxisMaxValue()
{
    return 32767;
}

int SDLJoystick::getAxisMinValue()
{
    return -32767;
}



bool SDLJoystick::init()
{
    if(controller == NULL && SDL_Init(SDL_INIT_JOYSTICK ) < 0){
        qDebug() << "failed " << SDL_GetError() << endl;
        return false;
    }

    if(SDL_NumJoysticks() < 1){
//        qDebug() << "no Joystick connected" << endl;
        return false;
    }else{
        controller = SDL_JoystickOpen(0);
        if(controller == NULL){
//            qDebug() << "Unable to open game controller " << SDL_GetError() << endl;
            return false;
        }else{
//            qDebug() << "The Joystick is connected " << endl;
            if(axes.size()==0 && buttons.size() == 0){
                axes.resize(SDL_JoystickNumAxes(controller));
                buttons.resize(SDL_JoystickNumButtons(controller));
            }
            return true;
        }
    }
}

void SDLJoystick::updateAxes(SDL_Event e)
{
    for(int i = 0; i < SDL_JoystickNumAxes(controller); i++){
        axes[i] = SDL_JoystickGetAxis(controller,i);
    }
    emit axesMoved();
}

void SDLJoystick::updateButtons(SDL_Event e)
{
    buttons[e.jbutton.button] = e.jbutton.state;
    emit buttonsChanged();
}


void SDLJoystick::checkSDLEvents()
{
    init();
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
