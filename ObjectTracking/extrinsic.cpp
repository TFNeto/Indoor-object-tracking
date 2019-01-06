#include "extrinsic.h"
#include "ui_extrinsic.h"
#include "global.h"
#include <string>

#include "camerafly.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int count = 0;

bool isCalibratingExtrinsic = false;
bool saveImageFlagExtrinsic = false;
bool discardImageFlagExtrinsic = false;
bool liveFlagExtrinsic = true;
FlyCapture2::Image convertedImageEX;

extrinsic::extrinsic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::extrinsic)
{
    ui->setupUi(this);
    for (uint i = 0; i<listOfCameras.size();i++ )
    {
        ui->comboBox->addItem(QString::fromStdString(listOfCameras[i].getIP()));
    }
    ui->comboBox->setCurrentIndex(0);
    for (uint i = 0; i<listOfCameras.size();i++ )
    {
        ui->comboBox_2->addItem(QString::fromStdString(listOfCameras[i].getIP()));
    }
    ui->numPicsDropdown->setValue(30);
    ui->numPicsDropdown->setVisible(true);
    ui->selectPair->setVisible(true);
    ui->photoCount->setVisible(true);
    ui->calibResult->setVisible(false);
    ui->calibResultText->setVisible(false);
    ui->numPicsText->setVisible(false);
    ui->camera1IP->setVisible(false);
    ui->camera2IP->setVisible(false);
    ui->saveButton->setVisible(false);
}

extrinsic::~extrinsic()
{
    delete ui;
}

void extrinsic::on_closeButton_clicked()
{
    isCalibratingExtrinsic = false;
    cv::destroyAllWindows();
    this->close();
}

void extrinsic::on_calibrateButton_clicked()
{
    if(ui->comboBox->currentIndex()!=ui->comboBox_2->currentIndex())
    {
        isCalibratingExtrinsic = true;
        ui->errorText->setVisible(false);
        ui->comboBox->setVisible(false);
        ui->comboBox_2->setVisible(false);
        ui->camera1IP->setText(ui->comboBox->currentText());
        ui->camera2IP->setText(ui->comboBox_2->currentText());
        ui->numPicsText->setText(QString::number( ui->numPicsDropdown->value()));
        ui->numPicsDropdown->setVisible(false);
        ui->numPicsText->setVisible(true);
        ui->camera1IP->setVisible(true);
        ui->camera2IP->setVisible(true);
        ui->calibrateButton->setVisible(false);
        /*
        uint ip1=listOfCameras[ui->comboBox->currentIndex()].getIpNumber();
        connectToCameraByIp(ip1);
        //connectToCameraByIp(ui->comboBox_2->currentIndex());
        //int index[2]={ui->comboBox->currentIndex(),ui->comboBox_2->currentIndex()};

        while(isCalibratingExtrinsic)
        {
            // Get image
            FlyCapture2::Image Image = takeSinglePictureFromSingleCamera(listOfCameras[ui->comboBox->currentIndex()].getIpNumber());
            unsigned int rowBytes = (double)Image.GetReceivedDataSize()/(double)Image.GetRows();
            cv::Mat imgcv = cv::Mat(Image.GetRows(), Image.GetCols(), CV_8UC3, Image.GetData(),rowBytes);
            // DEBUG: Show image using OpenCV's image display
            cv::imshow("image", imgcv);
            char key = cv::waitKey(1);

            // Show image
            if(liveFlagExtrinsic){
                cv::Mat show;
                cv::cvtColor(imgcv,show,CV_BGR2RGB);
                QImage img((uchar*)show.data, show.cols, show.rows, show.step, QImage::Format_RGB888);
                ui->camera1Feed->setPixmap(QPixmap::fromImage(img).scaled(630, 420, Qt::KeepAspectRatio));
                ui->camera1Feed->repaint();
                convertedImageEX=Image;

            }
        }*/
         //calibrateCameraPair();
        return;
    }
    ui->errorText->setText("Chose different cameras");
    ui->errorText->setVisible(true);
}

void extrinsic::calibrateCameraPair()
{

    int numOfPic = ui->numPicsDropdown->value();


    //do the calibration
}

void extrinsic::on_cancelButton_clicked()
{
    isCalibratingExtrinsic = false;
    cv::destroyAllWindows();
    ui->numPicsDropdown->setValue(30);
    ui->numPicsDropdown->setVisible(true);
    ui->selectPair->setVisible(true);
    ui->photoCount->setVisible(true);
    ui->calibResult->setVisible(false);
    ui->calibResultText->setVisible(false);
    ui->numPicsText->setVisible(false);
    ui->camera1IP->setVisible(false);
    ui->camera2IP->setVisible(false);
    ui->comboBox->setVisible(true);
    ui->comboBox_2->setVisible(true);
    ui->calibrateButton->setVisible(false);
}
