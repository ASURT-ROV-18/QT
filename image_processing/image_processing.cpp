#include "image_processing.h"
#include "mat_qimage.h"

using namespace std;
using namespace cv;
using namespace QtOcv;
using namespace DMCV;

Mat distanceMeasurement::originalImg;
Mat distanceMeasurement::finalImg;
int distanceMeasurement::callCounter = 0;
int distanceMeasurement::gaussianKernelSize = 7;
int distanceMeasurement::erosionHeightKernel = 3;
int distanceMeasurement::erosionWidthKernel = 1;
int distanceMeasurement::dilationHeightKernel = 7;
int distanceMeasurement::dilationWidthKernel = 3;
int distanceMeasurement::cannyMin = 50;
int distanceMeasurement::cannyMax = 200;
vector<Point2f> distanceMeasurement::centers;
double distanceMeasurement::areas = 0;
Mat distanceMeasurement::cameraMatrix = (Mat_<double>(3, 3) << 8.32406994e+02, 0.00000000e+00, 1.01754792e+03,
                                                               0.00000000e+00, 8.28474958e+02, 5.11095022e+02,
                                                               0.00000000e+00, 0.00000000e+00, 1.00000000e+00);
Mat distanceMeasurement::disCoeffs = (Mat_<double>(1, 5) << -0.37223564, 0.18453059, 0.00082939, 0.00081215, -0.04989387);


void distanceMeasurement::automaticDetection() {
    //gray-scale
    Mat grayScaleImg;
    cvtColor(originalImg, grayScaleImg, COLOR_BGR2GRAY);
    GaussianBlur(grayScaleImg, grayScaleImg, Size(gaussianKernelSize, gaussianKernelSize), 0);
#if DEBUG_STAGES
    imwrite("blur.png", grayScaleImg);
#endif
    //Canny detection
    Mat edgeImg;
    Canny(grayScaleImg, edgeImg, cannyMin, cannyMax, 3, true);
#if DEBUG_STAGES
    imwrite("canny.png", edgeImg);
#endif
    //close gaps between edges (vertical processing)
    Mat vEdgeImg;
    Mat vdKernel = getStructuringElement(CV_SHAPE_RECT, Size(dilationWidthKernel, dilationHeightKernel));
    Mat veKernel = getStructuringElement(CV_SHAPE_RECT, Size(erosionWidthKernel, erosionHeightKernel));
    dilate(edgeImg, vEdgeImg, vdKernel);
    erode(vEdgeImg, vEdgeImg, veKernel);
#if DEBUG_STAGES
    imwrite("vertical_processing.png", vEdgeImg);
#endif
    //close gaps between edges (horizontal processing)
    Mat hEdgeImg;
    Mat hdKernel = getStructuringElement(MORPH_RECT, Size(dilationHeightKernel, dilationWidthKernel));
    Mat heKernel = getStructuringElement(MORPH_RECT, Size(erosionHeightKernel, erosionWidthKernel));
    dilate(edgeImg, hEdgeImg, hdKernel);
    erode(hEdgeImg, hEdgeImg, heKernel);
#if DEBUG_STAGES
    imwrite("horizontal_processing.png", hEdgeImg);
#endif
    //combine horizontal and vertical processing
    Mat fineEdgeImg;
    bitwise_or(hEdgeImg, vEdgeImg, fineEdgeImg);
#if DEBUG_STAGES
    imwrite("combination.png", fineEdgeImg);
#endif
    //get centers of all boxes
    vector<vector<Point>> contours;
    Point2f vertices[4];
    double sumArea = 0;
    findContours(fineEdgeImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    for (unsigned int i = 0; i < contours.size(); ++i) {
        if (contourArea(contours[i]) < 1000)
            continue;
        cout << i << endl;
        RotatedRect rotatedRect = minAreaRect(contours[i]);
        sumArea += rotatedRect.size.area();
        rotatedRect.points(vertices);
        for(int k = 0; k < 4; ++k)
            cout << vertices[k] << "\t";
        cout << endl;
        for(int j = 0; j < 4; ++j)
            line(originalImg, vertices[j], vertices[(j + 1) % 4], Scalar(255, 0, 0), 1, CV_AA);
        centers.push_back(rotatedRect.center);
    }
    areas = sumArea / centers.size();
}

void distanceMeasurement::manualDetection() {

}

void distanceMeasurement::measureDistance(int method){
    callCounter++;
    double distance;
    int objectsNum;
    undistortion();
    if (method == automatic)
        automaticDetection();
    else if (method == manual)
        manualDetection();
    objectsNum = (int)centers.size();
    double px_m_ratio = sqrt(areas / cargoArea);
    finalImg = originalImg.clone();
    for (int i = 0; i < objectsNum; ++i) {
        distance = sqrt(pow((centers[i].x - centers[(i+1)%objectsNum].x), 2) + pow((centers[i].y - centers[(i+1)%objectsNum].y), 2));
        distance /= px_m_ratio;
        if(i != objectsNum-1 || objectsNum > 2)
            putText(finalImg, "distance from object "+to_string(i)+" to object "+to_string((i+1)%objectsNum)+" = "+
                    to_string(distance)+" m", Point(20, 40+40*i), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2, CV_AA);
        circle(finalImg, centers[i], 4, Scalar(0, 255, 0), 1, CV_AA);
        circle(finalImg, centers[(i+1)%objectsNum], 4, Scalar(0, 255, 0), 1, CV_AA);
        line(finalImg, centers[i], centers[(i+1)%objectsNum], Scalar(255, 0, 255), 2, CV_AA);
        putText(finalImg, "object: " + to_string(i), centers[i], FONT_HERSHEY_SIMPLEX,
                1, Scalar(0, 0, 255), 2, CV_AA);
    }
#if DEBUG_FINAL
    imwrite("final.png", finalImg);
#endif
}

void distanceMeasurement::undistortion(){
    Mat undistortedImage;
    undistort(originalImg, undistortedImage, cameraMatrix, disCoeffs);
#if DEBUG_DISTORTION
    imwrite("distorted.png", originalImg);
    imwrite("undistorted.png", undistortedImage);
#endif
    originalImg = undistortedImage.clone();
}

void distanceMeasurement::setImage(const QImage& image) {
   originalImg = image2Mat_shared(image);
}

void distanceMeasurement::writeImage() {
    imwrite("result_" + to_string(callCounter) + ".png", finalImg);
}

Mat distanceMeasurement::getImage() {
    return finalImg;
}
