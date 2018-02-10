#include <opencv2/opencv.hpp>
#include <QImage>
#include <cmath>

#define DEBUG_STAGES                1
#define DEBUG_FINAL                 1
#define DEBUG_DISTORTION            1
#define cargoArea                   0.006 //cargo area is 0.15 m2

enum method {automatic, manual};

namespace DMCV{
    class distanceMeasurement
    {
    private:
        static cv::Mat originalImg;
        static cv::Mat finalImg;
        static int callCounter;
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
        static void manualDetection();
        static void undistortion();
    public:
        static void setImage(const QImage& image);
        static cv::Mat getImage();
        static void measureDistance(int method=0);
        static void writeImage();
    };
}
