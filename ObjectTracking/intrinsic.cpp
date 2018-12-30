#include "intrinsic.h"
#include "ui_intrinsic.h"
#include "global.h"
#include "camerafly.h"
// #include "intrinsic_compute.h"

#include <iostream>
#include <sstream>
#include <unistd.h>



int counter = 0;

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
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->saveButton->setVisible(false);
    ui->repeatButton->setVisible(false);
    ui->saveImage->setVisible(false);
    ui->saveImageButton->setVisible(false);
}

Intrinsic::~Intrinsic()
{
    delete ui;
}

void Intrinsic::on_startCalibrButton_clicked()
{
    //check if camera is connected correctly
    //check is picture number is above 10 - add info stating bigger errors for less pictures
    //allow loading of external pictures
    calibrateCamera();
}

void Intrinsic::on_pictureButton_clicked()  // here is where the MAIGC HAPPENS
{
    // counter = counter + 1;
    ui->pictureButton->setVisible(false);

    // Get selected camera index
    int index = ui->cameraDropdown->currentIndex();
    // Get its IP (in decimal)
    uint camIpNumber = listOfCameras[index].getIpNumber();
    // Take picture (and save it)
    string fileName = takeSinglePictureFromSingleCamera(camIpNumber);
    // Show picture
    QImage myImage;
    myImage.load(QString::fromStdString(fileName), "png");
    ui->label_CameraFeed->setPixmap(QPixmap::fromImage(myImage).scaled(630, 420, Qt::KeepAspectRatio));
    ui->label_CameraFeed->repaint();

    ui->saveImage->setVisible(true);
    ui->saveImageButton->setVisible(true);
}

void Intrinsic::calibrateCamera()
{
     ui->pictureButton->setVisible(true);
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
    calibrateCamera();
}

void Intrinsic::on_saveButton_clicked()
{
    //save intrinsic parameters - intrinsic_compute doing this already
}

void Intrinsic::on_loadButton_clicked()
{
    //load parameters from xml file
}


