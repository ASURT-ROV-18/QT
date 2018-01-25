#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTimer>
#include <SFML/Window.hpp>
#include <QDesktopWidget>
#include <copilotscreen.h>

namespace Ui {
class PilotWindow;
}

class PilotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PilotWindow(QWidget *parent = 0);
    ~PilotWindow();

public:
    void on_actionOpen_co_pilot_screen_triggered();

private slots:
    void on_actionCo_pilot_ready_triggered();

private:
    Ui::PilotWindow *ui;
   // QTreeWidget *tree;
public:
    CoPilotScreen * CoPilotPointer;
};

#endif // DIALOG_H
