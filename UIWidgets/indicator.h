#pragma once

#include <QWidget>
#include "UIWidgets/qcontainer.h"

#include <QString>
//#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>

#define BOX_Size_Factor 1

namespace UIW {

class Indicator : public QWidget
{
    Q_OBJECT
private:
//    QGroupBox *_Box;
    QContainer *_Box;
    QLabel *_Label;
    QGridLayout *_Glayout;
    QString _unit;

    QWidget *_Parent_Widget;
public:

    Indicator(QWidget *parent){
        this->setParent(parent);

        _Parent_Widget = new QWidget(this);

//        _Box = new QGroupBox(this);
        _Box = new QContainer(this);
        _Glayout = new QGridLayout(_Box);
        _Label = new QLabel (_Box);

        _Glayout->addWidget(_Label,0,0,Qt::AlignCenter);
//      _Box->setLayout(_Glayout);

        _Label->setText("Indicator Value");
        _Box->setTitle("Indicator Title");

        _Label->setStyleSheet("QLabel{color: white ;  font-size: 20px; }");
//        _Box->setStyleSheet("QGroupBox{font-size: 15px; }");
        _Parent_Widget->setLayout(_Glayout);
        _Box->setWidget(_Parent_Widget);

//        _Label->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
//        _Box->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
//        this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//        this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

//        _Parent_Layout = new QGridLayout(this);
//        _Parent_Layout->addWidget(_Box,0,0/*,Qt::AlignTop|Qt::AlignLeft*/);

        _Box->setMinimumSize(_Box->sizeHint()*BOX_Size_Factor);
//        _Box->setFixedSize(_Box->sizeHint()*BOX_Size_Factor);

//        this->setGeometry(this->childrenRect());
//        this->updateGeometry();

        this->setFixedSize(this->childrenRect().size());

    }

    void setTitle(QString BoxTitle){
        _Box->setTitle(BoxTitle);
    }
    void setUnit(QString indicatorUnit){
        _unit = indicatorUnit;
    }

    QSize sizeHint(){
        return (_Box->sizeHint()*BOX_Size_Factor);
    }
    QSize minimumSizeHint(){
        return _Box->sizeHint();
    }
    void StretchIndicatorW(QSize newSize){
        _Box->setFixedWidth(newSize.width());
        this->setFixedSize(this->childrenRect().size());
    }
    void StretchIndicator(QSize newSize){
        _Box->setFixedSize(newSize);
        this->setFixedSize(this->childrenRect().size());
    }

    //~Indicator(){}

public slots:
    void updateValue(float value){
        _Label->setText(QString::number(value) +/*"\t"+*/ _unit);
//        qDebug() << "Value Set   "<<_Label->text();
    }

    void setText(QString Text){
        _Label->setText(Text);
    }
};
}
