#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QLabel>


class Clock : public QWidget
{
    Q_OBJECT
public:
    Clock(QWidget *parent, int minutes, int seconds);
    QLabel *stopWatchLabel;

private:
    QTimer *qTimer;
    QTime *timeValue;
    void setLabelColor(int minutes);
public slots:
    void setDisplay();
};

#endif // CLOCK_H
