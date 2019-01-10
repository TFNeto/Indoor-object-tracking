#include "realtimetracking.h"
#include "ui_realtimetracking.h"
#include <thread>
#include "camerafly.h"
#include "CamTracking.hpp"
#include <string>

#include "global.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

void trackingthread(int id)
{
    cv::Mat undistortedImg;
    // Get image from camera
    FlyCapture2::Image Image = takeSinglePictureFromSingleCamera(id);
    // Convert image to OpenCV Mat
    unsigned int rowBytes = static_cast<double>(Image.GetReceivedDataSize())/static_cast<double>(Image.GetRows());
    cv::Mat imgcv = cv::Mat(Image.GetRows(), Image.GetCols(), CV_8UC3, Image.GetData(),rowBytes);
    // Get intrinsic calib values
    cv::Mat cameraMatrix = listOfCameras[id].getCameraMatrix();
    cv::Mat distCoeffs = listOfCameras[id].getDistCoeffs();
    // Undistort image
    cv::undistort(imgcv, undistortedImg, cameraMatrix, distCoeffs);
    // Start tracking
    std::string trackerType = "CSRT";
    CamTracking ct(id, trackerType, undistortedImg);
    while(true)
    {
        cv::Mat undistortedImg;
        // Get image from camera
        FlyCapture2::Image Image = takeSinglePictureFromSingleCamera(id);
        // Convert image to OpenCV Mat
        unsigned int rowBytes = static_cast<double>(Image.GetReceivedDataSize())/static_cast<double>(Image.GetRows());
        cv::Mat imgcv = cv::Mat(Image.GetRows(), Image.GetCols(), CV_8UC3, Image.GetData(),rowBytes);
        // Undistort image
        cv::undistort(imgcv, undistortedImg, cameraMatrix, distCoeffs);
        vector<cv::Rect2d> pontos = ct.track(undistortedImg);
        // TODO: Set flag, or vector, or send some sort of signal to the parent thread
    }
}

RealTimeTracking::RealTimeTracking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RealTimeTracking)
{
    graph = new QtDataVisualization::Q3DScatter;
    container = QWidget::createWindowContainer(graph);
    modifier = new ScatterDataModifier(graph);
    modifier->addData();
    ui->setupUi(this);
    ui->gridLayout->addWidget(container);
    ui->stopRec_pushButton->setVisible(false);
}

RealTimeTracking::~RealTimeTracking()
{
    delete ui;
}

void RealTimeTracking::on_RandomizeButton_clicked()
{
    modifier->addData();
}

void RealTimeTracking::on_startRec_pushButton_clicked()
{
    ui->stopRec_pushButton->setVisible(true);
    ui->startRec_pushButton->setVisible(false);

    for(size_t i = 0; i < tvec.size(); i++)
    {
        tvec[i]->detach();
    }
}

void RealTimeTracking::on_stopRec_pushButton_clicked()
{
    ui->stopRec_pushButton->setVisible(false);
    ui->startRec_pushButton->setVisible(true);
    connectAllCameras();
    for(int i = 0; i < listOfCameras.size(); i++)
    {
        std::thread *t = new std::thread(trackingthread, i);
        tvec.push_back(t);
    }
    for(size_t i=0; i < tvec.size(); i++)
    {
        tvec[i]->detach();
    }
}
