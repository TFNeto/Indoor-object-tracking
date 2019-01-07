#include "intrinsic.h"
#include "ui_intrinsic.h"
#include "global.h"
#include "camerafly.h"

#include "intrinsic_compute.h"
#include <string>

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int counter = 0;
int numPhoto= 0;
string currentCamera;
string tempFilename;

// Save state of calibration process
// Enables live stream, if true
bool isCalibrating = false;
bool saveImageFlag = false;
bool discardImageFlag = false;
bool liveFlag = true;

FlyCapture2::Image convertedImage;

Intrinsic::Intrinsic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Intrinsic)
{
    ui->setupUi(this);
    for (uint i = 0; i<listOfCameras.size(); i++)
    {
        Camera cam = listOfCameras[i];
        ui->cameraDropdown->addItem(
                    QString::fromStdString(cam.getIP()) +
                    " ( " +
                    QString::fromStdString(std::to_string(cam.getX())) +
                    " , " +
                    QString::fromStdString(std::to_string(cam.getY())) +
                    " , " +
                    QString::fromStdString(std::to_string(cam.getZ())) +
                    " )"
        );
    }

    ui->pictureButton->setVisible(false);
    ui->numPicsDropdown->setValue(30);
    ui->imageProgressBar->setVisible(false);
    ui->saveButton->setVisible(false);
    ui->repeatButton->setVisible(false);
    ui->saveImage->setVisible(false);
    ui->saveImageButton->setVisible(false);
    ui->discardImageButton->setVisible(false);
    ui->numPics->setVisible(false);
    ui->labelCalibrationError->setVisible(false);
    ui->cancelCalibrationButton->setVisible(false);
    ui->cameraDropdown->setVisible(true);
    ui->cameraChosen->setVisible(false);
    ui->infoCalibration->setVisible(false);
}

Intrinsic::~Intrinsic()
{
    cv::destroyAllWindows();
    isCalibrating = false;
    delete ui;
}

void Intrinsic::on_startCalibrButton_clicked()
{
    numPhoto = ui->numPicsDropdown->value();
    counter = 0;
    cout << "DEBUG: Photos to be taken: " << numPhoto << endl;

    ui->cameraChosen->setText(ui->cameraDropdown->currentText());
    ui->cameraChosen->setVisible(true);
    ui->cameraDropdown->setVisible(false);
    ui->startCalibrButton->setVisible(false);
    ui->cancelCalibrationButton->setVisible(true);
    ui->numPicsDropdown->setVisible(false);
    ui->numPics->setVisible(true);
    ui->numPics->setText(QString::fromStdString(std::to_string(numPhoto)));
    ui->imageProgressBar->setRange(0,numPhoto);
    ui->imageProgressBar->setFormat("%v");
    ui->imageProgressBar->setVisible(true);
    ui->imageProgressBar->setValue(0);
    ui->pictureButton->setVisible(true);

    // Start live video
    isCalibrating = true;
    // Get selected camera index
    int index = ui->cameraDropdown->currentIndex();
    // Get its IP (in decimal)
    uint camIpNumber = listOfCameras[index].getIpNumber();
    // Connect to camera
    cout<<"gonna connect to "<< camIpNumber<<endl;
    cout<<"dropdown index :"<<ui->cameraDropdown->currentIndex()<<endl;
    int rightindex = connectToCameraByIp(camIpNumber);
    // Start capturing
    //connectToCameraByIp(listOfCameras[ui->cameraDropdown->currentIndex()].getIpNumber());
    while(isCalibrating)
    {
        // Get image
        FlyCapture2::Image Image = takeSinglePictureFromSingleCamera(rightindex);
        unsigned int rowBytes = (double)Image.GetReceivedDataSize()/(double)Image.GetRows();
        cv::Mat imgcv = cv::Mat(Image.GetRows(), Image.GetCols(), CV_8UC3, Image.GetData(),rowBytes);
        // DEBUG: Show image using OpenCV's image display
        cv::imshow("image", imgcv);
        char key = cv::waitKey(1);

        // Show image
        if(liveFlag){
            cv::Mat show;
            cv::cvtColor(imgcv,show,CV_BGR2RGB);
            QImage img((uchar*)show.data, show.cols, show.rows, show.step, QImage::Format_RGB888);
            ui->label_CameraFeed->setPixmap(QPixmap::fromImage(img).scaled(630, 420, Qt::KeepAspectRatio));
            ui->label_CameraFeed->repaint();
            convertedImage=Image;
        }

        // Save image if the user clicks on "Save"
        if(saveImageFlag) {
            string camIp = listOfCameras[ui->cameraDropdown->currentIndex()].getIP();
            saveImage(convertedImage, camIp, counter);
            saveImageFlag = false;
            liveFlag = true;

           /* if(counter == numPhoto)
            {
                ui->cameraDropdown->setVisible(true);
                ui->cameraChosen->setVisible(false);
                ui->infoCalibration->setVisible(true);

                cout << "Starting calib" << endl;
                //CORRER ROTINA DE CALIBRAÇÃO
                intrinsic_compute i;
                int nr_imagens = 8;
                string img_folder = "../home/dc/Downloads/seai2/build-ObjectTracking-Desktop_Qt_5_12_0_GCC_64bit-Debug";
                string img_filename = "calib169.254.193.167_";
                double a = i.run(nr_imagens, img_folder, img_filename);
                cout << "intrinsic calib: " << a << endl;
                //este filename pode ser o IP ou assim?
            isCalibrating = false;
            }*/
        }
        if(discardImageFlag) {
           discardImageFlag = false;
           liveFlag = true;
        }
    }
    // Disconnect from camera

    disconnectCameraByIp(camIpNumber);
    //stopRecording(ui->cameraDropdown->currentIndex());
}

void Intrinsic::on_pictureButton_clicked()
{
    liveFlag = false;
    ui->pictureButton->setVisible(false);
    ui->saveImage->setVisible(true);
    ui->saveImageButton->setVisible(true);
    ui->discardImageButton->setVisible(true);
  //  tempFilename.assign(fileName);
}

void Intrinsic::on_closeButton_clicked()
{
    //Check if it's mid calibration before closing
    //save current state?
    this->close();
}

void Intrinsic::on_repeatButton_clicked()
{
    //erase previous pictures from %foldername%
    //other important parameters reset?
    //"are you sure?" pop up box
    // calibrateCamera();
}

void Intrinsic::on_saveButton_clicked()
{
    //save intrinsic parameters - intrinsic_compute doing this already
}

void Intrinsic::on_loadButton_clicked()
{
    //load parameters from xml file
}

void Intrinsic::on_saveImageButton_clicked()
{
    counter++;
    saveImageFlag=true;
    ui->saveImage->setVisible(false);
    ui->saveImageButton->setVisible(false);
    ui->discardImageButton->setVisible(false);
    ui->pictureButton->setVisible(true);
    ui->imageProgressBar->setValue( counter );

}

void Intrinsic::on_discardImageButton_clicked()
{
    discardImageFlag=true;
    ui->saveImage->setVisible(false);
    ui->saveImageButton->setVisible(false);
    ui->discardImageButton->setVisible(false);
    ui->pictureButton->setVisible(true);
}

void Intrinsic::on_cancelCalibrationButton_clicked()
{
    // Stop calibration (this stops the live feed)
    isCalibrating = false;
    cv::destroyAllWindows();
    counter=0;
    ui->pictureButton->setVisible(false);
    ui->numPicsDropdown->setValue(30);
    ui->imageProgressBar->setVisible(false);
    ui->saveButton->setVisible(false);
    ui->repeatButton->setVisible(false);
    ui->saveImage->setVisible(false);
    ui->saveImageButton->setVisible(false);
    ui->discardImageButton->setVisible(false);
    ui->numPics->setVisible(false);
    ui->labelCalibrationError->setVisible(false);
    ui->cancelCalibrationButton->setVisible(false);
    ui->startCalibrButton->setVisible(true);
    ui->numPicsDropdown->setVisible(true);
    ui->cameraDropdown->setVisible(true);
    ui->cameraChosen->setVisible(false);
}
