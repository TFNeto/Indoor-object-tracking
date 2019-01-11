#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrate.h"
#include "configuration.h"
#include <QMessageBox>
#include "realtimetracking.h"
#include "trackinglog.h"
#include <string>
#include <vector>
#include "camera.h"
#include <utility>
#include "global.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "FlyCapture2.h"
#include "camerafly.h"

#include "CamTracking.hpp"

using namespace std;

static std::vector<std::vector<cv::Rect2d>> g_2dData;

vector<Camera> listOfCameras;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    camerasCalibrated = false;
    ui->setupUi(this);
    Configuration configWindow(this) ;
    Calibrate calibrationWindow;
    RealTimeTracking trackWindow;
    TrackingLog logWindow;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_configure_pushButton_clicked()
{
    configWindow.setModal(true);
    configWindow.exec();
}

void MainWindow::on_start_pushButton_clicked()
{
    /*
    if (this->camerasCalibrated)
    {
    */
        trackWindow.setModal(true);
        trackWindow.exec();
    /*}
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Cameras must be calibrated first."));
    }*/
}


void MainWindow::on_calibrate_pushButton_clicked()
{

    if(listOfCameras.empty())
    {
        QMessageBox::critical(this, tr("Error"), tr("There is no camera information. Go to Configuration to enter camera information."));
        return ;
    }

        calibrationWindow.setCameraInfo();
        calibrationWindow.setModal(true);
        calibrationWindow.exec();

}

void MainWindow::on_log_pushButton_clicked()
{
    logWindow.setModal(true);
    logWindow.exec();
}

void MainWindow::enablePushButtons()
{
    ui->start_pushButton->setEnabled(true);
    ui->configure_pushButton->setEnabled(true);
    ui->calibrate_pushButton->setEnabled(true);
    ui->log_pushButton->setEnabled(true);
}

void MainWindow::disablePushButtons()
{
    ui->start_pushButton->setDisabled(true);
    ui->configure_pushButton->setDisabled(true);
    ui->calibrate_pushButton->setDisabled(true);
    ui->log_pushButton->setDisabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    cout << "Begin test" << endl;
  /*  FileStorage fsl("a", FileStorage::READ);
    cv::Mat K, D;
    fsl["K"] >> K;
    fsl["D"] >> D;*/
    cv::Mat undistortedImg;
    // Get image from camera
    int id = connectToCameraByIp(listOfCameras[0].getIpNumber(), 'a');
    FlyCapture2::Image Image = takeSinglePictureFromSingleCamera(id);
    // Convert image to OpenCV Mat
    unsigned int rowBytes = static_cast<double>(Image.GetReceivedDataSize())/static_cast<double>(Image.GetRows());
    cv::Mat imgcv = cv::Mat(Image.GetRows(), Image.GetCols(), CV_8UC3, Image.GetData(),rowBytes);
    cv::imshow("before image", imgcv);
    char key = cv::waitKey(10);
    // Get intrinsic calib values
    cv::Mat K = listOfCameras[0].getCameraMatrix();
    cv::Mat D = listOfCameras[0].getDistCoeffs();
    // Undistort image
    cout << "K size: " << K.size() << endl;
    cout << "D size: " << D.size() << endl;

    cv::undistort(imgcv, undistortedImg, K, D);
    cv::imshow("after image", undistortedImg);
    key = cv::waitKey(10);
    cout << "Mid test" << endl;

}
