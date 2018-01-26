#include "imageprocessingscreen.h"
#include "ui_imageprocessingscreen.h"

const int point_size = 7;

ImageProcessingScreen::ImageProcessingScreen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ImageProcessingScreen) {
  ui->setupUi(this);
  QDir imgs;
  imgs.mkdir("./undistortedimgs/");
  _points = QVector<QVector<QPoint>>(4);
  _items = QVector<QVector<QGraphicsEllipseItem *>>(4);
  for (int i = 0; i < 4; ++i) {
    _points[i] = QVector<QPoint>();
    _items[i] = QVector<QGraphicsEllipseItem *>();
  }
  connect(ui->btnRefresh, SIGNAL(clicked(bool)), this, SLOT(refreshImages()));
  connect(ui->btnAuto, SIGNAL(clicked(bool)), this,
          SLOT(automaticProcessing()));
  connect(ui->btnManual, SIGNAL(clicked(bool)), this, SLOT(manualProcessing()));
  connect(ui->autoResultButton, SIGNAL(clicked(bool)), this,
          SLOT(showAutoRes()));
  connect(ui->manResultButton, SIGNAL(clicked(bool)), this, SLOT(showManRes()));
  _scene = new QGraphicsScene(this);
  ui->view->setScene(_scene);
  ui->view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  refreshImages();
}

void ImageProcessingScreen::refreshImages() {
  DMCV::distanceMeasurement::undistortImgs();
  QDir dir("./undistortedimgs/");
  auto old_len = _files.length();
  _files = dir.entryList(QStringList("*.png"),
                         QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks,
                         QDir::Time);
  if (_files.length() == 0) {
    displayEmptyImage();
  } else {
    _counter += _files.length() - old_len;
    displayImage(_counter);
  }
}

void ImageProcessingScreen::keyPressEvent(QKeyEvent *event) {
  if (event->isAutoRepeat()) {
    event->ignore();
    return;
  }
  switch (event->key()) {
  case Qt::Key_Right:
    displayImage(++_counter);
    break;
  case Qt::Key_Left:
    displayImage(--_counter);
    break;
  default:
    break;
  }
}

void ImageProcessingScreen::mousePressEvent(QMouseEvent *event) {
  auto p = ui->view->mapFromGlobal(event->globalPos()) +
           QPoint(ui->view->horizontalScrollBar()->value(),
                  ui->view->verticalScrollBar()->value());
  switch (event->button()) {
  case Qt::LeftButton: {
    if (_points[_rectangle_number].size() == 4)
      _rectangle_number++;
    _points[_rectangle_number].push_back(p);
    auto item =
        _scene->addEllipse(p.x() - point_size, p.y() - point_size, point_size,
                           point_size, QPen(), QBrush(Qt::red));
    _items[_rectangle_number].push_back(item);
  } break;
  case Qt::RightButton: {
    if (_points[_rectangle_number].isEmpty())
      if (_rectangle_number == 0)
        break;
      else
        _rectangle_number--;
    _points[_rectangle_number].pop_back();
    _scene->removeItem(_items[_rectangle_number].last());
    delete _items[_rectangle_number].last();
    _items[_rectangle_number].pop_back();
  } break;
  default:
    break;
  }
}

void ImageProcessingScreen::displayImage(int index) {
  _counter = (index + _files.length()) % _files.length();
  auto path = _files[_counter];
  auto img = QPixmap("./undistortedimgs/" + path);
  _scene->clear();
  _scene->addPixmap(img);
  _scene->setSceneRect(img.rect());
}

void ImageProcessingScreen::displayEmptyImage() {
  auto img = QPixmap(640, 480);
  img.fill(Qt::black);
  _scene->clear();
  _scene->addPixmap(img);
  _scene->setSceneRect(img.rect());
}

void ImageProcessingScreen::automaticProcessing() {
  DMCV::distanceMeasurement::setImage(_files[_counter]);
  DMCV::distanceMeasurement::measureDistance(DMCV::automatic);
}

void ImageProcessingScreen::manualProcessing() {
  DMCV::distanceMeasurement::setImage(_files[_counter]);
  DMCV::distanceMeasurement::measureDistance(DMCV::manual, _points);
  for (int i = 0; i < 4; ++i) {
    _points[i] = QVector<QPoint>();
    _items[i] = QVector<QGraphicsEllipseItem *>();
  }
}

void ImageProcessingScreen::showAutoRes() {
  auto path = _files[_counter];
  auto img = QPixmap("./auto_results/" + path);
  _scene->clear();
  _scene->addPixmap(img);
  _scene->setSceneRect(img.rect());
}

void ImageProcessingScreen::showManRes() {
  auto path = _files[_counter];
  auto img = QPixmap("./man_results/" + path);
  _scene->clear();
  _scene->addPixmap(img);
  _scene->setSceneRect(img.rect());
}

ImageProcessingScreen::~ImageProcessingScreen() { delete ui; }
