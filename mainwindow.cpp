#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QString>

PilotWindow::PilotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PilotWindow)
{
    ui->setupUi(this);
    CoPilotPointer = new CoPilotScreen();
    //m = new Dialog22();
}
 //DO NOT FORGET TO DELETE ALL POINTERS//
PilotWindow::~PilotWindow()
{
    delete CoPilotPointer;
    delete ui;
}

void PilotWindow::on_actionCo_pilot_ready_triggered()
{
    CoPilotPointer->setModal(true);
    CoPilotPointer->exec();
}
