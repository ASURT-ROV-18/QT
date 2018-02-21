#ifndef HANDLERSTHREAD_H
#define HANDLERSTHREAD_H
#include <QThread>
#include "mainwindow.h"

class HandlersThread : public QThread
{
    Q_OBJECT

protected:
    void run();
    MainWindow *mainWindow;
public:
    HandlersThread();
};

#endif // HANDLERSTHREAD_H
