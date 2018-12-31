#ifndef CAMERAFLY_H
#define CAMERAFLY_H

#include "FlyCapture2.h"
#include "camera.h"

void PrintError(FlyCapture2::Error error);
void PrintCameraInfo(FlyCapture2::CameraInfo *pCamInfo);
string takeSinglePictureFromSingleCamera(FlyCapture2::IPAddress ipAddress);
vector<Camera> scanCameras();

#endif // CAMERAFLY_H
