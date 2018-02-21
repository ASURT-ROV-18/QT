#ifndef HANDLERSTHREAD_H
#define HANDLERSTHREAD_H

#include <QThread>


class HandlersThread : public QThread
{
    Q_OBJECT

protected:
    void run();

public:
    HandlersThread();
};

#endif // HANDLERSTHREAD_H
