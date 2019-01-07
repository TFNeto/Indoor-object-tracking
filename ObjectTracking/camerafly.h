#ifndef CAMERAFLY_H
#define CAMERAFLY_H

#include "FlyCapture2.h"
#include "camera.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void PrintError(FlyCapture2::Error error);
void PrintCameraInfo(FlyCapture2::CameraInfo *pCamInfo);
FlyCapture2::Image takeSinglePictureFromSingleCamera(int index);
vector<Camera> scanCameras();
void startRecording(int index);
void stopRecording(int index);
int connectToCameraByIp(FlyCapture2::IPAddress ipAddress);
void disconnectCameraByIp(FlyCapture2::IPAddress ipAddress);
void saveImage(FlyCapture2::Image img, string camIp, int imgNum);

#endif // CAMERAFLY_H
