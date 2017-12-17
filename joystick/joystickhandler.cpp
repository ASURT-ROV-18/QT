#include "joystickhandler.h"
#include "sdljoystick.h"
#include <math.h>

int JoystickHandler::AXES_MESSAGE = 0;
int JoystickHandler::BUTTONS_MESSAGE = 1;
JoystickHandler::JoystickHandler(int libNumber)
{
    QObject(0);
    if(libNumber == SDLJoystick::SDLLIB)
        joystick = new SDLJoystick();

    if(joystick->isConnected()){
        axesLastValues.resize(joystick->getAxes().size());
        buttonsLastValues.resize(joystick->getButtons().size());
    }

    connect(joystick, SIGNAL(axesMoved()), this, SLOT(validateNewAxesData()));
    connect(joystick, SIGNAL(buttonsChanged()), this, SLOT(validateNewButtonsData()));
}

QVector<int> JoystickHandler::compareAxies(QVector<int> newReadings)
{
    QVector<int> diffs;
    for(int i = 0; i < newReadings.size(); i++){
        if(newReadings[i] != axesLastValues[i])
            diffs.push_back(i);
    }
    return diffs;
}

QVector<int> JoystickHandler::ignoreError(QVector<int> diffs, QVector<int> newReadings)
{
    int currentJSRange = joystick->getAxisMaxValue() - joystick->getAxisMinValue();
    float error = currentJSRange*(ERROR_PERCENTAGE/100.0);
    for(int i = 0; i < diffs.size(); i++){
        int absChangeValue= std::abs(axesLastValues[diffs[i]] - newReadings[diffs[i]]);
        if(absChangeValue <= error){
            diffs.remove(i);
            i--;
        }
    }
    return diffs;
}

void JoystickHandler::updateAxes(QVector<int> diffs, QVector<int> newReadings)
{
    for(int i = 0; i < diffs.size(); i++){
        axesLastValues[diffs[i]] = newReadings[diffs[i]];
    }
    emit sendJoystickData(buildMessage(AXES_MESSAGE, axesLastValues));
}

void JoystickHandler::updateButtons(QVector<int> diffs, QVector<int> newReadings)
{
    for(int i = 0; i < diffs.size(); i++){
        buttonsLastValues[diffs[i]] = newReadings[diffs[i]];
    }
    emit sendJoystickData(buildMessage(BUTTONS_MESSAGE, buttonsLastValues));
}

QString JoystickHandler::buildMessage(int messageType, QVector<int> values)
{
    //construct a message
    return QString("zai el fol");
}

QVector<int> JoystickHandler::compareButtons(QVector<int> newReadings)
{
    QVector<int> diffs;
    for(int i = 0; i < newReadings.size(); i++){
        if(newReadings[i] != buttonsLastValues[i])
            diffs.push_back(i);
    }
    return diffs;
}


void JoystickHandler::validateNewAxesData()
{
    QVector<int> newValues = joystick->getAxes();
    QVector<int> differences = compareAxies(newValues);
    differences = ignoreError(differences, newValues);
    qDebug() << differences << endl;
    updateAxes(differences, newValues);

}

void JoystickHandler::validateNewButtonsData()
{
    QVector<int> newValues = joystick->getAxes();
    QVector<int> differences = compareButtons(newValues);
    updateButtons(differences, newValues);
}


