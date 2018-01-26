#pragma once
#include <QDebug>
#include <QGlib/Connect>
#include <QGst/Buffer>
#include <QGst/Bus>
#include <QGst/ElementFactory>
#include <QGst/Init>
#include <QGst/Message>
#include <QGst/Parse>
#include <QGst/Pipeline>
#include <QGst/Sample>
#include <QGst/Structure>
#include <QGst/Ui/VideoWidget>
#include <QImage>

class Camera : public QGst::Ui::VideoWidget {
  Q_OBJECT
public:
  Camera(QWidget *parent = 0);
  ~Camera();
  QGst::State state() const;
  void init(QString ip, QString port);
  bool isPlaying();
  void play();
  void pause();
  void stop();
  QImage takeScreenshot();

signals:
  void stateChanged();

private:
  void setDescription(const QString &dsc);
  void onBusMessage(const QGst::MessagePtr &message);
  QGst::PipelinePtr _pipeline;
  QGst::ElementPtr _source;
  QGst::ElementPtr _sink;
};
