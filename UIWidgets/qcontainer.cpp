#include "qcontainer.h"

QContainer::QContainer(QWidget *parent) : QGroupBox(parent)
{
    this->setAlignment(Qt::AlignHCenter);
    _color = "white";
    _width = "3";
    this->setStyleSheet("QGroupBox{border-top-color:"+_color+";border-top-style:solid;border-top-width:"+_width+";border-left-color:"+_color+";border-left-style:solid;border-left-width:"+_width+";border-right-color:"+_color+";border-right-style:solid;border-right-width:"+_width+";border-bottom-color:"+_color+";border-bottom-style:solid;border-bottom-width:"+_width+";color:"+_color+";font-weight:bold;margin:5px;}QGroupBox::title {margin-top:-10px;margin-right:5px;margin-left:5px;}");
}

QContainer::QContainer(const QString & title,QWidget *parent) : QGroupBox(title,parent)
{
    this->setAlignment(Qt::AlignHCenter);
    _color = "white";
    _width = "3";
    this->setStyleSheet("QGroupBox{border-top-color:"+_color+";border-top-style:solid;border-top-width:"+_width+";border-left-color:"+_color+";border-left-style:solid;border-left-width:"+_width+";border-right-color:"+_color+";border-right-style:solid;border-right-width:"+_width+";border-bottom-color:"+_color+";border-bottom-style:solid;border-bottom-width:"+_width+";color:"+_color+";font-weight:bold;margin:5px;}QGroupBox::title {margin-top:-10px;margin-right:5px;margin-left:5px;}");
}

void QContainer::setColor(const QString & color){
    _color = color;
    this->setStyleSheet("QGroupBox{border-top-color:"+color+";border-top-style:solid;border-top-width:"+_width+";border-left-color:"+color+";border-left-style:solid;border-left-width:"+_width+";border-right-color:"+color+";border-right-style:solid;border-right-width:"+_width+";border-bottom-color:"+color+";border-bottom-style:solid;border-bottom-width:"+_width+";color:"+color+";font-weight:bold;margin:5px;}QGroupBox::title {margin-top:-10px;margin-right:5px;margin-left:5px;}");
}

void QContainer::setWidth(const QString & width){
    _width = width;
    this->setStyleSheet("QGroupBox{border-top-color:"+_color+";border-top-style:solid;border-top-width:"+width+";border-left-color:"+_color+";border-left-style:solid;border-left-width:"+width+";border-right-color:"+_color+";border-right-style:solid;border-right-width:"+width+";border-bottom-color:"+_color+";border-bottom-style:solid;border-bottom-width:"+width+";color:"+_color+";font-weight:bold;margin:5px;}QGroupBox::title {margin-top:-10px;margin-right:5px;margin-left:5px;}");
}

void QContainer::setWidget(QWidget *widget){
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    scrollArea->setWidgetResizable( true );
    scrollArea->setWidget( widget );
    scrollArea->setStyleSheet("QScrollArea{border:0px;}");
    QVBoxLayout * scroll = new QVBoxLayout;
    scroll->addWidget(scrollArea);
    scroll->setMargin(5);
    this->setLayout(scroll);
}
