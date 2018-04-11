#include "iprectangle.h"
#include <QPainter>
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>

int IPRectangle::WIDTH = 300;
int IPRectangle::HIGHT = 200;

IPRectangle::IPRectangle(QWidget *parent)
{
    this->setParent(parent);
}

void IPRectangle::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);


    QRect rec = QApplication::desktop()->screenGeometry();
    int left = 0.5*rec.width() - WIDTH + WIDTH*0.25;
    int top = 0.5*rec.height() - HIGHT;


    QRect r1(left, top, WIDTH, HIGHT);
    QPen pen;
    pen.setColor("red");
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawRect(r1);
}

