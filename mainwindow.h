#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt5GStreamer/QGst/Pipeline>
#include <Qt5GStreamer/QGst/Ui/VideoWidget>
#include <videostream/camera.h>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Camera* player1 = new Camera(), Camera* player2 = new Camera);
    ~MainWindow();
    void setCams(Camera* player1, Camera* player2);



private:
    QGst::PipelinePtr m_pipeline, videosrc;
    QGst::State state() const;
    Camera* player1;
    Camera* player2;

    QTabWidget *tabWidget;
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
