#ifndef QCONTAINER_H
#define QCONTAINER_H

#include <QWidget>
#include <QGroupBox>
#include <QScrollArea>
#include <QVBoxLayout>

class QContainer : public QGroupBox
{
    Q_OBJECT
private:
    QString _color;
    QString _width;

public:
    explicit QContainer(QWidget *parent = 0);
    explicit QContainer(const QString & title,QWidget *parent = 0);
    void setColor(const QString & color);
    void setWidth(const QString & width);
    void setWidget(QWidget * widget);

signals:

public slots:
};

#endif // QCONTAINER_H
