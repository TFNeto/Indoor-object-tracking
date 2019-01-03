#ifndef CAMERAFLY_H
#define CAMERAFLY_H

#include "FlyCapture2.h"
#include "camera.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void PrintError(FlyCapture2::Error error);
void PrintCameraInfo(FlyCapture2::CameraInfo *pCamInfo);
FlyCapture2::Image takeSinglePictureFromSingleCamera();
vector<Camera> scanCameras();
void connectToCameraByIp(FlyCapture2::IPAddress ipAddress);
void disconnectCamera();
void saveImage(FlyCapture2::Image img);

#endif // CAMERAFLY_H
