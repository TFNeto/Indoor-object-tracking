#include "extrinsic.h"
#include "ui_extrinsic.h"
#include "global.h"
#include <string>
#include "extrinsic_compute.h"
#include "camerafly.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
int counterEx=0;
int numPhotoEx=0;

bool isCalibratingExtrinsic = false;
bool saveImageFlagExtrinsic = false;
bool discardImageFlagExtrinsic = false;
bool liveFlagExtrinsic = true;
FlyCapture2::Image convertedImageEX;
FlyCapture2::Image convertedImageEX2;

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
    ui->takePictureButton->setVisible(false);
    ui->savePictureButton->setVisible(false);
    ui->discardPictureButton->setVisible(false);
    ui->imageProgressBar->setValue(0);
    ui->imageProgressBar->setVisible(false);
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

void extrinsic::on_takePictureButton_clicked()
{
    liveFlagExtrinsic=false;
    ui->takePictureButton->setVisible(false);
    ui->savePictureButton->setVisible(true);
    ui->discardPictureButton->setVisible(true);

}

void extrinsic::on_savePictureButton_clicked()
{
    counterEx++;
    ui->imageProgressBar->setValue(counterEx);
    ui->takePictureButton->setVisible(true);
    ui->savePictureButton->setVisible(false);
    ui->discardPictureButton->setVisible(false);
    saveImageFlagExtrinsic=true;
}

void extrinsic::on_discardPictureButton_clicked()
{
    ui->takePictureButton->setVisible(true);
    ui->savePictureButton->setVisible(false);
    ui->discardPictureButton->setVisible(false);
    discardImageFlagExtrinsic=true;
}

void extrinsic::on_calibrateButton_clicked()
{

    if(ui->comboBox->currentIndex() != ui->comboBox_2->currentIndex())
    {
        ui->imageProgressBar->setVisible(true);
        numPhotoEx=ui->numPicsDropdown->value();
        isCalibratingExtrinsic = true;
        ui->numPicsDropdown->setVisible(false);
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
        ui->takePictureButton->setVisible(true);
        ui->calibrateButton->setVisible(false);

        int index1 = connectToCameraByIp(listOfCameras[ui->comboBox->currentIndex()].getIpNumber(),'s');
        int index2 = connectToCameraByIp(listOfCameras[ui->comboBox_2->currentIndex()].getIpNumber(),'s');

        while(isCalibratingExtrinsic)
        {
            // Get image
            FlyCapture2::Image Image = takeSinglePictureFromSingleCamera(index1);
            FlyCapture2::Image Image2 = takeSinglePictureFromSingleCamera(index2);

            unsigned int rowBytes = (double)Image.GetReceivedDataSize()/(double)Image.GetRows();
            cv::Mat imgcv = cv::Mat(Image.GetRows(), Image.GetCols(), CV_8UC3, Image.GetData(),rowBytes);

            unsigned int rowBytes2 = (double)Image2.GetReceivedDataSize()/(double)Image2.GetRows();
            cv::Mat imgcv2 = cv::Mat(Image2.GetRows(), Image2.GetCols(), CV_8UC3, Image2.GetData(),rowBytes);

            // DEBUG: Show image using OpenCV's image display
            cv::imshow("image", imgcv);
            char key = cv::waitKey(1);
            cv::imshow("image2", imgcv2);
            key = cv::waitKey(1);
            // Show image
            if(liveFlagExtrinsic)
            {
                cv::Mat show;
                cv::Mat show2;
                cv::cvtColor(imgcv,show,CV_BGR2RGB);
                cv::cvtColor(imgcv2,show2,CV_BGR2RGB);
                QImage img((uchar*)show.data, show.cols, show.rows, show.step, QImage::Format_RGB888);
                QImage img2((uchar*)show2.data, show2.cols, show2.rows, show2.step, QImage::Format_RGB888);
                ui->camera1Feed->setPixmap(QPixmap::fromImage(img).scaled(441, 294, Qt::KeepAspectRatio));
                ui->camera1Feed->repaint();
                ui->camera2Feed->setPixmap(QPixmap::fromImage(img2).scaled(441, 294, Qt::KeepAspectRatio));
                ui->camera2Feed->repaint();
                convertedImageEX=Image;
                convertedImageEX2=Image2;
           }
           if(saveImageFlagExtrinsic)
           {
               string camIp1 = listOfCameras[ui->comboBox->currentIndex()].getIP();
               saveImage(convertedImageEX, camIp1, counterEx);
               string camIp2=listOfCameras[ui->comboBox_2->currentIndex()].getIP();
               saveImage(convertedImageEX2, camIp2, counterEx);
               saveImageFlagExtrinsic = false;
               liveFlagExtrinsic = true;
                if(counterEx == numPhotoEx)
                {
                    extrinsic_compute e;
                    //test vars
                    int counter = numPhotoEx; //number of photos
                    string leftcalib_file = "calib" + camIp1 + "_" + ".yml";
                    string rightcalib_file = "calib" + camIp2 + "_" + ".yml";
                    string leftimg_dir = "";
                    string rightimg_dir = "";
                    string leftimg_filename = "calib" + camIp1 + "_";
                    string rightimg_filename = "calib" + camIp2 + "_";
                    string out_file = "teste_pair.yml";
                    e.run_extrinsic(counter, leftcalib_file, rightcalib_file, leftimg_dir, rightimg_dir, leftimg_filename, rightimg_filename, out_file);
                    isCalibratingExtrinsic=false;
                }
            }
            if (discardImageFlagExtrinsic)
            {
                discardImageFlagExtrinsic = false;
                liveFlagExtrinsic = true;
            }
        }
        calibrateCameraPair();
        disconnectCameraByIp(listOfCameras[ui->comboBox->currentIndex()].getIpNumber());
        return; // TODO: This is useless ?
    }
    ui->errorText->setText("Chose different cameras");
    ui->errorText->setVisible(true);
}

void extrinsic::calibrateCameraPair()
{
    int numOfPic = ui->numPicsDropdown->value();

//    extrinsic_compute e;
//    //test vars
//    int counter = numOfPic; //number of photos
//    string leftcalib_file = "cam_out_intrinsic_left.yml";
//    string rightcalib_file = "cam_out_intrinsic_righ.yml";
//    string leftimg_dir = "../1";
//    string rightimg_dir = "../1";
//    string leftimg_filename = "left";
//    string rightimg_filename = "right";
//    string out_file = "teste_pair.yml";
//    e.run_extrinsic(counter, leftcalib_file, rightcalib_file, leftimg_dir, rightimg_dir, leftimg_filename, rightimg_filename, out_file);

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
