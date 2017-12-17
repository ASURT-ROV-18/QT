#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QWidget *parent = 0);
    ~Player();

    void init();


signals:
    void stoppedStreaming();

public slots:
    bool play();
};

#endif
