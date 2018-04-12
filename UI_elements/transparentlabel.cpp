#include "transparentlabel.h"
#include <QDebug>



TransparentLabel::TransparentLabel(QWidget *parent, QString fixedPart)
{
   // this->setParent(parent);
    this->fixedText = fixedPart;
    this->label = new QLabel(this);
    label->setStyleSheet("QLabel{color: orange ;  font-size: 40px; }");
    label->setFixedWidth(300);
    this->setText("");
}

void TransparentLabel::setText(QString text)
{
    label->setText(fixedText + " : " + text);
}


