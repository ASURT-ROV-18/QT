#pragma once

#include <QDebug>
#include <QDir>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>
#include <QPoint>
#include <QScrollBar>
#include <QStringList>
#include <QVector>
#include "image_processing/image_processing.h"

namespace Ui {
class ImageProcessingScreen;
}

class ImageProcessingScreen : public QMainWindow {
  Q_OBJECT

public:
  explicit ImageProcessingScreen(QWidget *parent = 0);
  ~ImageProcessingScreen();

protected:
  void keyPressEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
private slots:
  void refreshImages();
  void automaticProcessing();
  void manualProcessing();
  void showAutoRes();
  void showManRes();

private:
  void displayImage(int index);
  void displayEmptyImage();
  Ui::ImageProcessingScreen *ui;
  QStringList _files;
  int _counter = 0;
  int _rectangle_number = 0;
  QVector<QVector<QPoint>> _points;
  QVector<QVector<QGraphicsEllipseItem *>> _items;
  QGraphicsScene *_scene;
};
