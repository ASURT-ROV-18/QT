#include "camera.h"
// TODO: reconnect on error

Camera::Camera(QWidget *parent, QString discription) : QGst::Ui::VideoWidget(parent) {
  QGst::init();
  this->discription = discription;
}

void Camera::play() {
  if (_pipeline) {
    _pipeline->setState(QGst::StatePlaying);
  }
}

void Camera::pause() {
  if (_pipeline) {
    _pipeline->setState(QGst::StatePaused);
  }
}
void Camera::stop() {
//  if (_pipeline) {
//    emit stateChanged();
//  }
    if (_pipeline) {
      _pipeline->setState(QGst::StateNull);
      _pipeline->bus()->removeSignalWatch();
    }
}

QGst::State Camera::state() const {
  return _pipeline ? _pipeline->currentState() : QGst::StateNull;
}

void Camera::init() {
//   TODO: use ip, port when recv from rpi
//    setDescription(
//        "udpsrc port=5000 ! "
//        "application/"
//        "x-rtp,media=(string)video,clock-rate=(int)90000,encoding-name=("
//        "string)JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc");
//    setDescription(
//        "v4l2src device=/dev/video0 ! video/x-raw,framerate=30/1,width=1280,height=720 ! va   apipostproc");
  setDescription(this->discription);
  QGst::BusPtr bus = _pipeline->bus();
  bus->addSignalWatch();
  QGlib::connect(bus, "message", this, &Camera::onBusMessage);
}

bool Camera::isPlaying() { return state() == QGst::StatePlaying; }

void Camera::setDescription(const QString &dsc) {
  _source = QGst::Bin::fromDescription(dsc);
  _sink = QGst::ElementFactory::make("qwidget5videosink");
  _sink->setProperty("sync", false);
  _sink->setProperty("enable-last-sample", true);
  setVideoSink(_sink);
  _pipeline = QGst::Pipeline::create();
  _pipeline->add(_source);
  _pipeline->add(_sink);
  _source->link(_sink);

}

void Camera::onBusMessage(const QGst::MessagePtr &message) {
  switch (message->type()) {
  case QGst::MessageEos:
    stop();
    break;
  case QGst::MessageError:
    qDebug() << message.staticCast<QGst::ErrorMessage>()->error();
    stop();
    break;
  case QGst::MessageStateChanged:
    if (message->source() == _pipeline)
      emit stateChanged();
    break;
  default:
    break;
  }
}

QImage Camera::takeScreenshot() {
  QGst::SamplePtr sample =
      _sink->property("last-sample").get<QGst::SamplePtr>();
  QGst::BufferPtr buffer = sample->buffer();
  QGst::CapsPtr caps = sample->caps();
  QGst::MapInfo mapInfo;
  const QGst::StructurePtr structure = caps->internalStructure(0);
  int width, height;

  width = structure.data()->value("width").get<int>();
  height = structure.data()->value("height").get<int>();

  auto data = buffer->map(mapInfo, QGst::MapRead) ? mapInfo.data() : nullptr;
  QImage img;

  // img = QImage(data, width, height, QImage::Format_ARGB32);

  img = QImage(data, width, height, QImage::Format_RGB32);

  buffer->unmap(mapInfo);

  return img;
}


Camera::~Camera() {
  if (_pipeline) {
    _pipeline->setState(QGst::StateNull);
    _pipeline->bus()->removeSignalWatch();
  }
}
