#include "realtimetracking.h"
#include "ui_realtimetracking.h"
#include <thread>
#include "camerafly.h"
#include "camera.h"
#include "CamTracking.hpp"
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//pontosPorCam[4]
//[vector<cv::Rect2d>, vector<cv::Rect2d>, vector<cv::Rect2d>, vector<cv::Rect2d>]

void trackingthread(int id)
{
    cv::Mat undistortedImg;
    // Get image from camera
    FlyCapture2::Image camImg = takeSinglePictureFromSingleCamera(id);
    // Get intrinsic calib values
    //cv::Mat cameraMatrix = listOfCameras[id].
    //cv::Mat distCoeffs = listOfCameras[id].
    // Undistort image
    //cv::undistort(camImg, undistortedImg, cameraMatrix, distCoeffs);
    // Start tracking
    std::string trackerType = "CSRT";
    CamTracking ct(id, trackerType, undistortedImg);
    while(true)
    {
        cv::Mat undistortedImg;
        // Get image from camera
        FlyCapture2::Image camImg = takeSinglePictureFromSingleCamera(id);
        // Undistort image
        //cv::undistort(camImg, undistortedImg, cameraMatrix, distCoeffs);
        vector<cv::Rect2d> pontos = ct.track(undistortedImg);
        // Send signal/pontos to main thread
        //pontosPorCam[id] = pontos
        //send ABC1
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

    for(size_t i=0;i<tvec.size();i++){
        tvec[i]->detach();
    }

}

void RealTimeTracking::on_stopRec_pushButton_clicked()
{
    ui->stopRec_pushButton->setVisible(false);
    ui->startRec_pushButton->setVisible(true);
    // TODO: Call connectToAllCameras()
    int numCams = 4; // TODO: Get numCams from the listOfCameras vector
    for(int i=0;i<numCams;i++){
        std::thread *t = new std::thread(trackingthread,i);
        tvec.push_back(t);
    }
    for(size_t i=0;i<tvec.size();i++){
        tvec[i]->detach();
    }
}
