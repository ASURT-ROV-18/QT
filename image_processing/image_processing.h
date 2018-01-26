#include <QDebug>
#include <QDir>
#include <QImage>
#include <QPoint>
#include <QString>
#include <QVector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <set>

#define DEBUG_STAGES 0
#define cargoArea 0.15 // cargo area is 0.15 m2

namespace DMCV {
enum method { automatic, manual };
class distanceMeasurement {
private:
  static cv::Mat originalImg;
  static cv::Mat finalImg;
  static QString imgName;
  static int gaussianKernelSize;
  static int erosionHeightKernel;
  static int erosionWidthKernel;
  static int dilationHeightKernel;
  static int dilationWidthKernel;
  static int cannyMin;
  static int cannyMax;
  static cv::Mat cameraMatrix;
  static cv::Mat disCoeffs;
  static std::vector<cv::Point2f> centers;
  static double areas;
  static void automaticDetection();
  static void manualDetection(QVector<QVector<QPoint>> points);

public:
  static void setImage(QString path);
  static void undistortImgs();
  static QImage getImage();
  static void measureDistance(int method, QVector<QVector<QPoint>> points =
                                              QVector<QVector<QPoint>>(0));
};
}
