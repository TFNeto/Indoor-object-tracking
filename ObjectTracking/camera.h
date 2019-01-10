#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <string>
#include <QDataStream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;

class Camera
{
private:
    string name;
    string IPaddress;
    float xPosition, yPosition, zPosition;
    float pointingAngle;
    bool isCalibratedIntrinsic = false;
    bool isCalibratedExtrinsic = false;
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
public:
    Camera(string name, string IPaddress, float xPosition, float yPosition, float zPosition, float pointingAngle);
    Camera();
    string getName(void);
    string getIP(void);
    float getX(void);
    float getY(void);
    float getZ(void);
    float getAngle(void);
    uint getIpNumber(void);
    bool isIntrinsicCalibrated(void);
    bool isExtrinsicCalibrated(void);
    cv::Mat getCameraMatrix(void);
    cv::Mat getDistCoeffs(void);
    void setIsCalibratedIntrinsic(void);
    void setIsCalibratedExtrinsic(void);
    void setCameraMatrix(cv::Mat cameraMatrix);
    void setDistCoeffs(cv::Mat distCoeffs);
};

QDataStream &operator<<(QDataStream &out, const Camera &cam);
QDataStream &operator>>(QDataStream &in, Camera &cam);
#endif // CAMERA_H
