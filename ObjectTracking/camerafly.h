#ifndef CAMERAFLY_H
#define CAMERAFLY_H

#include "FlyCapture2.h"
#include "camera.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void PrintError(FlyCapture2::Error error);
void PrintCameraInfo(FlyCapture2::CameraInfo *pCamInfo);
cv::Mat takeSinglePictureFromSingleCamera(FlyCapture2::IPAddress ipAddress);
vector<Camera> scanCameras();

#endif // CAMERAFLY_H
