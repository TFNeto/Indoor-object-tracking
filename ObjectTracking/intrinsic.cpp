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

#include <QMessageBox>

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
    ui->numPicsDropdown->setMinimum(25);
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
    this->isCalibrating = false;
    delete ui;
}

void Intrinsic::on_startCalibrButton_clicked()
{
    if(listOfCameras[ui->cameraDropdown->currentIndex()].isIntrinsicCalibrated())
    {
        return;
    }
    this->numPhoto = ui->numPicsDropdown->value();
    this->counter = 0;
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
    this->isCalibrating = true;
    // Get selected camera index
    int index = ui->cameraDropdown->currentIndex();
    // Get its IP (in decimal)
    uint camIpNumber = listOfCameras[index].getIpNumber();
    // Connect to camera
    int rightindex = connectToCameraByIp(camIpNumber,'a');
    // Start capturing
    //connectToCameraByIp(listOfCameras[ui->cameraDropdown->currentIndex()].getIpNumber());
    while (this->isCalibrating)
    {
        // Get image
        FlyCapture2::Image Image = takeSinglePictureFromSingleCamera(rightindex);
        unsigned int rowBytes = static_cast<double>(Image.GetReceivedDataSize())/static_cast<double>(Image.GetRows());
        cv::Mat imgcv = cv::Mat(Image.GetRows(), Image.GetCols(), CV_8UC3, Image.GetData(),rowBytes);
        // DEBUG: Show image using OpenCV's image display
        cv::imshow("image", imgcv);
        char key = cv::waitKey(1);

        // Show image
        if (this->liveFlag)
        {
            cv::Mat show;
            cv::cvtColor(imgcv,show,CV_BGR2RGB);
            QImage img(static_cast<uchar*>(show.data), show.cols, show.rows, show.step, QImage::Format_RGB888);
            ui->label_CameraFeed->setPixmap(QPixmap::fromImage(img).scaled(630, 420, Qt::KeepAspectRatio));
            ui->label_CameraFeed->repaint();
            convertedImage = Image;
        }

        // Save image if the user clicks on "Save"
        if (this->saveImageFlag)
        {
            string camIp = listOfCameras[ui->cameraDropdown->currentIndex()].getIP();
            saveImage(convertedImage, camIp, counter);
            this->saveImageFlag = false;
            this->liveFlag = true;

            if(counter == numPhoto)
            {
                // Start calibration
                ui->cameraDropdown->setVisible(true);
                ui->cameraChosen->setVisible(false);
                ui->infoCalibration->setVisible(true);

                cout << "DEBUF: Starting intrinsic calibation on camera ip" << camIp << endl;

                intrinsic_compute i;
                string img_folder = "";
                string img_filename = "calib" + camIp +"_";
                img_filename.erase(std::remove(img_filename.begin(), img_filename.end(), '.'), img_filename.end());
                double intrinsicCalibError = i.run(numPhoto, img_folder, img_filename);

                cout << "DEBUG: Instrinsic calibration (error) result: " << intrinsicCalibError << endl;

                if (intrinsicCalibError <= 0)
                {
                    QMessageBox::critical(this, tr("Error"), tr("Intrinsic calibration failed."));
                } else
                {
                    string infoMessage = "Intrinsic calibration succeeded. Error value: " + to_string(intrinsicCalibError);
                    QMessageBox::information(this, tr("Intrinsic calibration"), tr(infoMessage.c_str()));
                    listOfCameras[index].setIsCalibratedIntrinsic();
                    listOfCameras[index].setDistCoeffs(i.getDistCoeffs());
                    listOfCameras[index].setCameraMatrix(i.getCameraMatrix());
                }
                this->isCalibrating = false;
                ui->cancelCalibrationButton->setVisible(false);
                ui->startCalibrButton->setVisible(true);
                ui->infoCalibration->setVisible(false);
            }
        }
        // Discard image if the user clicks on "Discard"
        if (this->discardImageFlag)
        {
            this->discardImageFlag = false;
            this->liveFlag = true;
        }
    }
    // Disconnect camera
    disconnectCameraByIp(camIpNumber);
    // stopRecording(ui->cameraDropdown->currentIndex());
}

void Intrinsic::on_pictureButton_clicked()
{
    this->liveFlag = false;
    ui->pictureButton->setVisible(false);
    ui->saveImage->setVisible(true);
    ui->saveImageButton->setVisible(true);
    ui->discardImageButton->setVisible(true);
    // tempFilename.assign(fileName);
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
    string camIp ="calib"+ listOfCameras[ui->cameraDropdown->currentIndex()].getIP()+"_";
    camIp.erase(std::remove(camIp.begin(), camIp.end(), '.'), camIp.end());
    cout<<camIp<<endl;
    FileStorage fsl(camIp, FileStorage::READ);
    Mat K ,D ;
    fsl["K"] >> K;
    fsl["D"] >> D;
    listOfCameras[ui->cameraDropdown->currentIndex()].setDistCoeffs(D);
    listOfCameras[ui->cameraDropdown->currentIndex()].setCameraMatrix(K);

    cout<<listOfCameras[ui->cameraDropdown->currentIndex()].getCameraMatrix()<<endl;



}

void Intrinsic::on_saveImageButton_clicked()
{
    this->counter++;
    this->saveImageFlag = true;
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
    this->isCalibrating = false;
    cv::destroyAllWindows(); // Debug ?
    this->counter = 0;
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
