#pragma once

#include <QWidget>

#include <QTimer>
#include <QLabel>
#include <QString>

#include <QGridLayout>

#define Max_MINUTE 15

namespace UIW {

class Timer :public QWidget
{
    Q_OBJECT
private:
    QTimer *_Timer;
    QLabel *_Label;
    QString _Min_Time;
    QString _Sec_Time;

    QGridLayout *_Parent_Layout;

    int _Tsec;
    int _Tmin;
    int _Total_Time;

public:

    Timer(QWidget *parent,unsigned int Total_Mins = Max_MINUTE){
        this->setParent(parent);

        _Timer = new QTimer(this);
        _Total_Time = Total_Mins;

        _Label = new QLabel(this);
        _Label->setStyleSheet("QLabel{color: white ;  font-size: 20px; }");
        _Label->setAlignment(Qt::AlignHCenter);
//        _Label->setAlignment(Qt::AlignTop);
        _Label->setAlignment(Qt::AlignVCenter);

        connect( _Timer , SIGNAL(timeout()),this,SLOT(updateTimer()));

        Initialize(_Total_Time);
        //Start();

        //_Label->setMinimumSize(_Label->sizeHint());
        _Label->setMaximumSize(_Label->sizeHint());

        this->setFixedSize(_Label->size());

        //_Parent_Layout = new QGridLayout(this);
        //_Parent_Layout->addWidget(_Label,0,0);

    }
    //~Timer(){}

    QSize sizeHint(){
        return (_Label->sizeHint());
    }
    QSize minimumSizeHint(){
        return _Label->sizeHint();
    }

    void Initialize(int Total_Mins){
        _Label->setText(QString::number(Total_Mins) + ":00");
        _Tmin = Total_Mins;
        _Tsec = 0;
    }

    void Start(){
        _Timer->start(1000);
    }
    void Reset(){
        _Timer->stop();
        Initialize(_Total_Time);
        Start();
    }
public slots:
    void updateTimer(){
        if(_Tsec == 0){
            _Tmin--;
            _Tsec = 59;
        }else{
            _Tsec--;
        }
        _Min_Time.clear();
        _Sec_Time.clear();

        if(_Tmin<10) _Min_Time += "0";
        _Min_Time += QString::number(_Tmin);

        if(_Tsec<10) _Sec_Time += "0";
        _Sec_Time += QString::number(_Tsec);

        _Label->setText(_Min_Time + ":" + _Sec_Time);

        if((_Tsec==0)&(_Tmin==0)) _Timer->stop();
    }
    void startCounting(){
        Reset();
    }
};
}

// Here Lies Parts of the Code that used 2 QLCDNumber instead of QLabel in displaying the Timer
/*
#include <QLCDNumber>

QGridLayout *_GLayout;
QLCDNumber *_Min_LCD;
QLCDNumber *_Sec_LCD;

_GLayout = new QGridLayout(this);
_Min_LCD = new QLCDNumber (this);
_Sec_LCD = new QLCDNumber (this);
_GLayout->addWidget(_Min_LCD , 0,0);
_GLayout->addWidget(_Sec_LCD , 0,1);

this->setLayout(_GLayout);


_Min_LCD->display(Total_Mins);
_Sec_LCD->display(0);

_Min_LCD-> display(Tmin);
_Sec_LCD-> display(Tsec);
*/
