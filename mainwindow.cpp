#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <videostream/camera.h>
#include <QWidget>
#include <QGridLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <UI_elements/clock.h>
#include <QHBoxLayout>
//#include "image_processing/image_processing.h"
//#include "image_processing/mat_qimage.h"

//using namespace std;
//using namespace cv;
//using namespace QtOcv;
//using namespace DMCV;

MainWindow::MainWindow(QWidget *parent, Camera* player1, Camera* player2, bool timer) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(0,0,1280,720);


    masterWidget =  new QWidget();
    masterWidgetLayout = new QGridLayout(masterWidget);
//    masterWidgetLayout->setColumnStretch(0, 7);
//    masterWidgetLayout->setColumnStretch(1, 3);
    masterWidget->setLayout(masterWidgetLayout);


    tabWidget = new QTabWidget(this);
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    tabWidget->setTabPosition(QTabWidget::TabPosition(2));
    this->setCentralWidget(tabWidget);

//    connect(this, SIGNAL(changeTab(int)), tabWidget, SLOT(tabChanged(int)));

    this->player1 = player1;
    this->player2 = player2;

    centralWidgetTab1 = new QWidget();
    centralGridTab1 = new QGridLayout(centralWidgetTab1);
    centralGridTab1->setMargin(0);

    centralGridTab1->setHorizontalSpacing(0);
    centralGridTab1->setVerticalSpacing(0);

    centralWidgetTab1->setLayout(centralGridTab1);

    centralWidgetTab2 = new QWidget();
    centralGridTab2 = new QGridLayout(centralWidgetTab2);
    centralGridTab2->setMargin(0);

    centralWidgetTab3 = new QWidget();
    centralGridTab3 = new QGridLayout(centralWidgetTab3);
    centralGridTab3->setMargin(0);


    tabWidget->insertTab(0, centralWidgetTab1, tr("Cam1"));
    tabWidget->insertTab(1, centralWidgetTab2, tr("Cam2"));
    tabWidget->insertTab(2, centralWidgetTab3, tr("cam 1, 2"));



//    //external camera stream
//    player1->init("v4l2src device=/dev/video1 ! image/jpeg, width=1280, height=720, framerate=60/1 ! rtpjpegpay ! application/x-rtp,media=(string)video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc", "5000");
//    player1->play();


//    //webcam stream
//    player1->init("v4l2src device=/dev/video0 ! video/x-raw, framerate=30/1,widtb=1280,heigt=720 ! vaapipostproc","");
//    player1->play();




//    //webcam stream
//    player2->init("v4l2src device=/dev/video0 ! video/x-raw, framerate=30/1,widtb=1280,heigt=720 ! vaapipostproc","");
//    player2->play();




//      //external camera udp stream
////    player2->init("udpsrc port=5000 ! application/x-rtp,media=(string)video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc", "5000");
////    player2->play();
    if(timer){        
        clock = new Clock(masterWidget, 15, 0);
        masterWidgetLayout->addWidget(clock, 0, 0);
        masterWidgetLayout->setRowStretch(0, 4);
        masterWidgetLayout->setRowStretch(1, 1);
        axisLabel = new TransparentLabel(masterWidget, "Z Axis");
        masterWidgetLayout->addWidget(axisLabel);
//        rectangle = new IPRectangle(masterWidget);
//        masterWidgetLayout->addWidget(rectangle, 0, 0);
    }
}





MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCams(Camera *player1, Camera *player2)
{
    this->player1 = player1;
    this->player2 = player2;
}

void MainWindow::changeTab(int index)
{
    emit tabWidget->currentChanged(index);
}


void MainWindow::tabChanged(int index)
{
    if(index == 0){
        centralGridTab1->addWidget(player1, 0, 0);
        centralGridTab1->addWidget(masterWidget, 0, 0);
        if(rectangle != NULL){
            rectangle->setVisible(true);
        }
    }else if(index == 1){
        centralGridTab2->addWidget(player2, 0, 0);
        centralGridTab2->addWidget(masterWidget, 0, 0);
        if(rectangle != NULL){
            rectangle->setVisible(false);
        }
    }else if(index == 2){
        centralGridTab3->addWidget(player1, 0, 0);
        centralGridTab3->addWidget(player2, 0, 1);
        centralGridTab3->addWidget(masterWidget, 0, 0);
        if(rectangle != NULL){
            rectangle->setVisible(false);
        }
    }
}

void MainWindow::updateAxesLabel(QVector<int> axes)
{
    this->axisLabel->setText(QString("%1").arg(100-(int)(((axes[3]/327.67)+100)/2) ,3 , 10, QChar('0')));
}

void MainWindow::keyPressEvent(QKeyEvent* event) {

    if(event->key() == Qt::Key_Space){
        qDebug() << event->key();
        if(this->rectangle->isVisible())
          this->rectangle->setVisible(false);
        else
            this->rectangle->setVisible(true);
    }
}
