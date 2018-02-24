#include "joystickhandler.h"
#include "sdljoystick.h"
#include <QTime>
#include "mainwindow.h"


int JoystickHandler::AXES_MESSAGE = 0;
int JoystickHandler::BUTTONS_MESSAGE = 1;
JoystickHandler::JoystickHandler(int libNumber)
{
    QObject(0);
    this->libNumber = libNumber;
    init(libNumber);
}

JoystickHandler::JoystickHandler(int libNumber, NetworkHandler *networkHandler )
{
    QObject(0);
    init(libNumber);
    QTimer *checkConnectionTimer = new QTimer(this);
    connect(checkConnectionTimer, SIGNAL(timeout()),this, SLOT(reconnect()));
//    connect(checkConnectionTimer, SIGNAL(timeout()),this, SLOT(send()));
    checkConnectionTimer->start(100);
//    connect(this, SIGNAL(sendJoystickData_noargs(QString)), networkHandler, SLOT(sendUDPMessage(QString)));
    connect(this, SIGNAL(sendJoystickData_noargs(QString)), networkHandler, SLOT(sendTCPMessage(QString)));

    qDebug() << "Joystick handler" << endl;
}

JoystickHandler::JoystickHandler(int libNumber, NetworkHandler *networkHandler, MainWindow *mainWindow)
{
    init(libNumber);
    QTimer *checkConnectionTimer = new QTimer(this);
    connect(checkConnectionTimer, SIGNAL(timeout()),this, SLOT(reconnect()));
//    connect(checkConnectionTimer, SIGNAL(timeout()),this, SLOT(send()));
    checkConnectionTimer->start(100);
//    connect(this, SIGNAL(sendJoystickData_noargs(QString)), networkHandler, SLOT(sendUDPMessage(QString)));
    connect(this, SIGNAL(sendJoystickData_noargs(QString)), networkHandler, SLOT(sendTCPMessage(QString)));
    this->mainWindow = mainWindow;

    qDebug() << "Joystick handler" << endl;


}

JoystickHandler::~JoystickHandler()
{
    if(joystick != NULL)
        delete joystick;
}

void JoystickHandler::send(){
    emit sendJoystickData_noargs(buildMessage_noargs());
}

QVector<int> JoystickHandler::compareAxes(QVector<int> newReadings)
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
    if(diffs.size() != 0)
        emit sendJoystickData_noargs(buildMessage_noargs());
}

void JoystickHandler::updateButtons(QVector<int> diffs, QVector<int> newReadings)
{
    for(int i = 0; i < diffs.size(); i++){
        buttonsLastValues[diffs[i]] = newReadings[diffs[i]];
    }


    if(buttonsLastValues[1] == 1){
        qDebug() << buttonsLastValues << endl;
        int cInd = mainWindow->tabWidget->currentIndex();
        mainWindow->tabWidget->setCurrentIndex((++cInd)%3);
    }

    if(buttonsLastValues[11] == 1){
        qDebug() << buttonsLastValues << endl;
        mainWindow->clock->start();
    }




    emit sendJoystickData_noargs(buildMessage_noargs());
}

QString JoystickHandler::buildMessage_noargs()
{
    QString message = " ";

    message += "x " + QString("%1").arg((int)(axesLastValues[0]/327.67) ,6 , 10, QChar('0'));
    message += "; y " + QString("%1").arg((int)(-1*axesLastValues[1]/327.67) ,6 , 10, QChar('0'));
    message += "; r " + ((buttonsLastValues[0] == 1) ? QString("%1").arg((int)(axesLastValues[2]/327.67) ,6 , 10, QChar('0')) : "000000");
    message += "; z " + QString("%1").arg(100-(int)(((axesLastValues[3]/327.67)+100)/2) ,6 , 10, QChar('0')) + "; ";
    message += "up "+ QString("%1").arg(buttonsLastValues[4],1,10, QChar('0')) + "; ";
    message += "down "+ QString("%1").arg(buttonsLastValues[2],1,10, QChar('0')) + " ";
    message += ";";

    qDebug() << message;
    return message;
    qDebug() << message;
    return message;
}

QString JoystickHandler::buildMessage(int messageType, QVector<int> values)
{
    QString message = " ";

//    message = QString("%1").arg("x ", values[0],"; y ", values[1], "; r ", values[2], "; z ", values[3]);
//    message.append(arg("x ", values[0],"; y ", values[1], "; r ", values[2], "; z ", values[3])
//    message += "x " + values[0] + "; y " + values[1] + "; r " + values[2] + "; z " + values[3];

    message += "x " + QString("%1").arg((int)(values[0]/327.67) ,3 , 10, QChar('0')) + "; y " +
            QString("%1").arg((int)(values[1]/327.67) ,3 , 10, QChar('0')) + "; r " +
            QString("%1").arg((int)(values[2]/327.67) ,3 , 10, QChar('0')) + "; z " +
            QString("%1").arg((int)(((values[3]/327.67)+100)/2) ,3 , 10, QChar('0')) + "; ";

//    for(int i = 0; i < values.size(); i++){
//        message.append(QString("%1").arg(values[i],
//                                         (messageType == JoystickHandler::AXES_MESSAGE)? 6 : 1,
//                                                    10, QChar('0')) + " ");
//    }
//    if(messageType == JoystickHandler::BUTTONS_MESSAGE)
//        return QString("Buttons " + message);
//    else if(messageType == JoystickHandler::AXES_MESSAGE)
//        return QString("Axes " + message);
//    else return NULL;
//    qDebug() << message;
    return message;
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

void JoystickHandler::init(int libNumber)
{
    if(libNumber == SDLJoystick::SDLLIB && joystick == NULL){
        joystick = new SDLJoystick();
        connect(joystick, SIGNAL(axesMoved()), this, SLOT(validateNewAxesData()));
        connect(joystick, SIGNAL(buttonsChanged()), this, SLOT(validateNewButtonsData()));
    }
    if(joystick->isConnected()){
        if(axesLastValues.size() == 0 && buttonsLastValues.size() == 0){
            axesLastValues.resize(joystick->getAxes().size());
            buttonsLastValues.resize(joystick->getButtons().size());
        }
    }
}


void JoystickHandler::validateNewAxesData()
{
    QVector<int> newValues = joystick->getAxes();
    QVector<int> differences = compareAxes(newValues);
    differences = ignoreError(differences, newValues);
//    qDebug() << newValues << endl;
    updateAxes(differences, newValues);
}

void JoystickHandler::validateNewButtonsData()
{
    QVector<int> newValues = joystick->getButtons();
    QVector<int> differences = compareButtons(newValues);
    updateButtons(differences, newValues);
}

void JoystickHandler::reconnect()
{
    if(joystick->isConnected()){
        this->init(libNumber);
    }
}
