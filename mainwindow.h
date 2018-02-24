#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt5GStreamer/QGst/Pipeline>
#include <Qt5GStreamer/QGst/Ui/VideoWidget>
#include <videostream/camera.h>
#include <QGridLayout>
#include <UI_elements/clock.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Camera* player1 = new Camera(), Camera* player2 = new Camera, bool timer = true);
    ~MainWindow();
    void setCams(Camera* player1, Camera* player2);
    void changeTab(int index);
    QTabWidget *tabWidget;
    Clock *clock;



private:
    QGst::PipelinePtr m_pipeline, videosrc;
    QGst::State state() const;
    Camera* player1;
    Camera* player2;

    QWidget *centralWidgetTab1;
    QGridLayout *centralGridTab1;
    QWidget *centralWidgetTab2;
    QGridLayout *centralGridTab2;
    QWidget *centralWidgetTab3;
    QGridLayout *centralGridTab3;
    QWidget *masterWidget;
    QGridLayout *masterWidgetLayout;
    Ui::MainWindow *ui;



private slots:
    void tabChanged(int index);
};


#endif // MAINWINDOW_H
