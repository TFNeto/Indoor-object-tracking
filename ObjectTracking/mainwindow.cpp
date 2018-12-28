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

using namespace std;

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
    if (this->camerasCalibrated)
    {
        trackWindow.setModal(true);
        trackWindow.exec();
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Cameras must be calibrated first."));
    }
}


void MainWindow::on_calibrate_pushButton_clicked()
{
    /*if (listOfCameras.size()!=0)
    {
    */
        calibrationWindow.setCameraInfo(this->loadCameraMock());
        calibrationWindow.setCameraInfo(listOfCameras);
        calibrationWindow.setModal(true);
        calibrationWindow.exec();
    /*
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("There is no camera information. Go to Configuration to enter camera information."));
    }*/
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


vector<Camera> MainWindow::loadCameraMock(){
    vector<Camera> mockCameras;
    Camera cam1("cam1", "IP1", 0,0,2.5,0);
    Camera cam2("cam2", "IP2", 0,5,2.5,0);

    mockCameras.push_back(cam1);
    mockCameras.push_back(cam2);
    return mockCameras;
}