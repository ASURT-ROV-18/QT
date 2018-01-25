#include "copilotscreen.h"
#include "ui_copilotscreen.h"

#define First_Row 0
#define Second_Row 2
#define Third_Row 4

#define First2Second_Row 1
#define Second2Third_Row 3

#define First_Column 0
#define Second_Column 2
#define Third_Column 4

#define First2Second_Column 1
#define Second2Third_Column 3

#include <QDebug>

CoPilotScreen::CoPilotScreen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CoPilotScreen) {
  ui->setupUi(this);
  this->setWindowTitle("CoPilot Screen");

  _Central_Widget = new QWidget(this);
  _Master_Camera = new QWidget(/*ui->centralwidget*/ /*this*/ _Central_Widget);
  _Master_Widget = new QWidget(/*ui->centralwidget*/ /*this*/ _Central_Widget);
  _Central_Grid =
      new QGridLayout(/*ui->centralwidget*/ /*this*/ _Central_Widget);
  _Master_Grid = new QGridLayout(_Master_Widget);
  _Master_Camera->setStyleSheet("background-color: blue;");
  _Central_Grid->addWidget(_Master_Camera, 0, 0);
  _Central_Grid->addWidget(_Master_Widget, 0, 0);
  _Central_Grid->setMargin(0);
  //    _Master_Widget->raise();

  _Central_Widget->setLayout(_Central_Grid);
  this->setCentralWidget(_Central_Widget);

  _Master_Widget->setLayout(_Master_Grid);

  _Timer = new UIW::Timer(this);
  _Depth_Indicator = new UIW::Indicator(this);
  _Score_Indicator = new UIW::Indicator(this);
  _Missions = new UIW::Missions(this);
  _SBar = new UIW::statusBar(this);
  _Rotate_Label = new UIW::RotatableLabel(this);

  _joystick = new JS::Joystick();
  _connection = new connection();

  _Master_Grid->addWidget(_Depth_Indicator, First_Row, First_Column,
                          Qt::AlignTop | Qt::AlignLeft);
  _Master_Grid->addWidget(_Timer, First_Row, Second_Column,
                          Qt::AlignTop | Qt::AlignHCenter);
  _Master_Grid->addWidget(_Score_Indicator, First_Row, Third_Column,
                          Qt::AlignTop /*| Qt::AlignRight*/);
  _Master_Grid->addWidget(_Missions, Second_Row, Third_Column,
                          Qt::AlignTop | Qt::AlignRight);
  _Master_Grid->addWidget(_SBar, Third_Row, First_Column, 1,
                          Third_Column + 1 /*,Qt::AlignBottom*/);
  _Master_Grid->addWidget(_Rotate_Label, Second_Row, First_Column,
                          Qt::AlignTop);

  connect(_joystick, SIGNAL(update(std::unordered_map<std::string, float>)),
          _connection, SLOT(write(std::unordered_map<std::string, float>)));
  connect(_connection, SIGNAL(networkState(bool)), _SBar,
          SLOT(ethernetConnected(bool)));
  connect(_connection, SIGNAL(TCPState(bool)), _SBar, SLOT(RPiConnected(bool)));
  connect(_joystick, SIGNAL(connected(bool)), _SBar,
          SLOT(joystickConnected(bool)));

//  connect(_SBar , SIGNAL(updateMode(std::unordered_map<std::string,std::string>))
//          , _connection , SLOT(write(std::unordered_map<std::string,float>)));

  //    connect(this,SIGNAL(updateDepth(float)),_Depth_Indicator,SLOT(updateValue(float)));
  connect(this, SIGNAL(starTimerCounting()), _Timer, SLOT(startCounting()));
  //    connect(this,SIGNAL(updateCycles(float)),_SBar,SLOT(gripCycles(float)));
  connect(_Missions, SIGNAL(ourCurrentScore(float)), _Score_Indicator,
          SLOT(updateValue(float)));
  connect(_Missions, SIGNAL(returnFocus()), this, SLOT(getFocus()));

  // ********* Master Grid Size Modifications***************

  _Master_Grid->setVerticalSpacing(10);

  //    _Master_Grid->setRowStretch(First_Row,0);
  //    _Master_Grid->setRowStretch(First2Second_Row,0);
  //    _Master_Grid->setRowStretch(Second_Row,0);
  _Master_Grid->setRowStretch(Second2Third_Row, 3);
  //    _Master_Grid->setRowStretch(Third_Row,0);

  //    _Master_Grid->setColumnStretch(First_Column,0);
  _Master_Grid->setColumnStretch(First2Second_Column, 2);
  //    _Master_Grid->setColumnStretch(Second_Column,0);
  _Master_Grid->setColumnStretch(Second2Third_Column, 2);
  //    _Master_Grid->setColumnStretch(Third_Column,0);

  //***********************************************************

  _Score_Indicator->StretchIndicatorW(_Missions->size());

  _Depth_Indicator->setTitle("Depth");
  _Score_Indicator->setTitle("Total Score");
  _Score_Indicator->setUnit("/" + QString::number(_Missions->getTopScore()));
  _Score_Indicator->setText("0/" + QString::number(_Missions->getTopScore()));

  _Rotate_Label->setFile(
      "/home/zaher/RacingTeam/ROV'17/QT_Codes/New GUI/gui/ROV_Planes.png");
  this->setFocus();

  _joystick->init();
  _connection->initializeConnection(QHostAddress("12.0.0.145"), 8005, true);
}

CoPilotScreen::~CoPilotScreen() { delete ui; }

void CoPilotScreen::keyPressEvent(QKeyEvent *event) {
  //**********Ignore Holding and consider it as a single click
  if (event->isAutoRepeat()) {
    event->ignore();
    return;
  }
  //*************************************************************

  if ((event->key() == Qt::Key_Enter) |
      (event->key() == Qt::Key_Return)) { // For Both Enters in the keyboard
    qDebug() << "Enter";
    //        _Timer->startCounting(); // Warning : could restart Timer while
    //        running just by pressing Enter
  } else if (event->key() == Qt::Key_Up) {
    qDebug() << "Up";
  } else if (event->key() == Qt::Key_Down) {
    qDebug() << "Down";
  } else if (event->key() == Qt::Key_Right) {
    qDebug() << "Right";
  } else if (event->key() == Qt::Key_Left) {
    qDebug() << "Left";
  } else if (event->key() == Qt::Key_M) {
    qDebug() << "M";
    _SBar->mode_list->showPopup();
  } else if (event->key() == Qt::Key_C) {
    qDebug() << "C";
  } else if (event->key() == Qt::Key_Space) {
    qDebug() << "Space Bar";
    if (!_Master_Widget->isHidden()) {
      _Master_Widget->hide();
    } else {
      _Master_Widget->show();
    }
  } else if (event->key() == Qt::Key_T) {
    qDebug() << "T";
    _Timer->startCounting();
  }
}

void CoPilotScreen::getFocus() { this->setFocus(); }

QWidget *CoPilotScreen::getCentralWidget() { return _Master_Widget; }
