#pragma once

#include <QLabel>
#include <QBitmap>
#include <QPixmap>
//#include <QDesktopWidget>

namespace UIW
{

class RotatableLabel : public QLabel
{
    Q_OBJECT
public:

    RotatableLabel(QWidget *parent = 0) : QLabel(parent),
        pix(new QPixmap()),
        rotPix(new QPixmap()),
        transform(new QTransform())
    {
        label = new QLabel(this);
        transform->reset();
        oldAngle=0;
    }
    void rotate(int degree)
    {
        oldAngle=degree;
        transform->rotate(degree);

        *rotPix = pix->transformed(*transform);

        int x = (rotPix->width()  - pix->width())  / 2;
        int y = (rotPix->height() - pix->height()) / 2;

        *rotPix = rotPix->copy(x, y, pix->width(), pix->width());

        setPixmap(*rotPix);

        transform->reset();
    }
    void setFile(const QString &file)
    {
        setStyleSheet("border:transparent;background: transparent");
        pix->load(file);
        setPixmap(*pix);
        this->setDimensions();
    }
    int oldangle()
    {
        return oldAngle;
    }
    void setpixmap(QPixmap* pixmap)
    {
        pix=pixmap;
    }
    void setDimensions (void)
    {
        int height = pix->height();
        QRect *frame= new QRect();
        frame->setWidth(height);
        frame->setHeight(height);
        this->setGeometry(*frame);
    }



private:
    QPixmap *pix, *rotPix;
    QTransform *transform;
    QLabel *label;
    int oldAngle;
public slots:
    void rovRoll (int angle)
    {
        this->rotate(angle);
    }
    void rovYaw (int angle)
    {
        this->rotate(angle);
    }

};

}
