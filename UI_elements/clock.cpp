#include "clock.h"
#include <QDebug>

Clock::Clock(QWidget *parent, int minutes, int seconds)
{
    this->setParent(parent);
    this->stopWatchLabel = new QLabel(this);

    qTimer = new QTimer(this);
    timeValue = new QTime(0, minutes, seconds);

    setLabelColor(minutes);

    stopWatchLabel->setFixedWidth(100);
    stopWatchLabel->setText(timeValue->toString().mid(3));

    QObject::connect(qTimer,SIGNAL(timeout()),this,SLOT(setDisplay()));
    qTimer->start(1000);

}

void Clock::setLabelColor(int minutes)
{
    if(minutes < 5 && minutes >= 2){
        stopWatchLabel->setStyleSheet("QLabel{color: orange ;  font-size: 40px; }");
    }
    else if(minutes < 2){
        stopWatchLabel->setStyleSheet("QLabel{color: red ;  font-size: 40px; }");
    }else{
        stopWatchLabel->setStyleSheet("QLabel{color: green ;  font-size: 40px; }");
    }
}

void Clock::setDisplay()
{
    if(timeValue == NULL)
        return;
    int minutes = timeValue->addSecs(-1).minute();
    int seconds = timeValue->addSecs(-1).second();

    if(seconds == 0 && minutes == 0){
        timeValue = NULL;
        stopWatchLabel->setText(" ");
        return;
    }

    timeValue->setHMS(0, minutes, seconds);
    setLabelColor(minutes);
    stopWatchLabel->setText(timeValue->toString().mid(3));
}
