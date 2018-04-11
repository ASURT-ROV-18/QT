#ifndef IPRECTANGLE_H
#define IPRECTANGLE_H

#include <QWidget>


class IPRectangle : public QWidget
{
    Q_OBJECT
public: 
    IPRectangle(QWidget *parent);
    static int WIDTH;
    static int HIGHT;

private:
    void paintEvent(QPaintEvent *e);
};

#endif // IPRECTANGLE_H
