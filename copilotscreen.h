#ifndef COPILOTSCREEN_H
#define COPILOTSCREEN_H

#include <QMainWindow>

#include <QGridLayout>
#include <QKeyEvent>

#include "UIWidgets/indicator.h"
#include "UIWidgets/missions.h"
#include "UIWidgets/modeList.h"
#include "UIWidgets/statusbar.h"
#include "UIWidgets/timer.h"
#include "UIWidgets/rotatablelabel.h"

#include "joystick/joystick.h"
#include "connection/connection.h"

namespace Ui {
class CoPilotScreen;
}

class CoPilotScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit CoPilotScreen(QWidget *parent = 0);
    ~CoPilotScreen();

    QWidget *getCentralWidget();

private:
    Ui::CoPilotScreen *ui;

    QWidget *_Central_Widget;
    QWidget *_Master_Widget;
    QWidget *_Master_Camera;

    QGridLayout *_Master_Grid;
    QGridLayout *_Central_Grid;

    UIW::Indicator *_Depth_Indicator;
    UIW::Indicator *_Score_Indicator;
    UIW::Missions *_Missions;
    UIW::Timer *_Timer;
    UIW::statusBar *_SBar;
    UIW::RotatableLabel *_Rotate_Label;

    JS::Joystick *_joystick;
    connection *_connection;

signals:
    void updateDepth(float); // communication
    void updateScore(float); // TreeWidget
    void starTimerCounting(); // Keyboard
    void updateCycles(float); // Keyboard

public slots:
    void keyPressEvent( QKeyEvent* event );
    void getFocus();
};

#endif // COPILOTSCREEN_H
