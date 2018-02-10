//#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include <QDebug>
//#include <QWidget>
//#include <QLabel>
//#include <QBoxLayout>
//#include <camera.h>
//#include <QWidget>
//#include <QGridLayout>
//#include <QTabWidget>

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//    this->setGeometry(0,0,900,900);


//    QTabWidget *tabWidget = new QTabWidget(this);
//    tabWidget->setTabPosition(QTabWidget::TabPosition(2));

//    QWidget *centralWidgetTab1 = new QWidget();

//    player1 = new Camera(centralWidgetTab1);
//    QGridLayout *centralGridTab1 = new QGridLayout(centralWidgetTab1);
//    centralGridTab1->addWidget(player1, 0, 0);
//    centralGridTab1->setMargin(0);
//    centralWidgetTab1->setLayout(centralGridTab1);
//    this->setCentralWidget(tabWidget);



//    QWidget *centralWidgetTab2 = new QWidget();

//    player2 = new Camera(centralWidgetTab2);
//    QGridLayout *centralGridTab2 = new QGridLayout(centralWidgetTab2);
//    centralGridTab2->addWidget(player2, 0, 0);
//    centralGridTab2->setMargin(0);


//    QWidget *centralWidgetTab3 = new QWidget();
//    QGridLayout *centralGridTab3 = new QGridLayout(centralWidgetTab3);
////    centralGridTab3->addWidget(player1, 0, 0);
////    centralGridTab3->addWidget(player2, 0, 1);
//    centralGridTab3->setMargin(0);



//    centralWidgetTab2->setLayout(centralGridTab2);
//    this->setCentralWidget(tabWidget);


//    tabWidget->insertTab(0, centralWidgetTab1, tr("Cam1"));
//    tabWidget->insertTab(1, centralWidgetTab2, tr("Cam2"));
////    tabWidget->insertTab(2, centralWidgetTab3, tr("cam 1, 2"));

//    player1->init("v4l2src device=/dev/video1 ! image/jpeg, width=1280, height=720, framerate=60/1 ! rtpjpegpay ! application/x-rtp,media=(string)video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc", "5000");
//    player1->play();



//    player2->init("udpsrc port=5000 ! application/x-rtp,media=(string)video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc", "5000");
//    player2->play();
//}



//MainWindow::~MainWindow()
//{
//    delete ui;
//}
