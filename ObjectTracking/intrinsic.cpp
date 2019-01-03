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

int counter = 0;
int numPhoto= 0;
string currentCamera;
string tempFiliname;

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
    delete ui;
}

void Intrinsic::on_startCalibrButton_clicked()
{
    //check if camera is connected correctly
    //check is picture number is above 10 - add info stating bigger errors for less pictures
    //allow loading of external pictures
    calibrateCamera();
}

void Intrinsic::on_pictureButton_clicked()
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
    ui->discardImageButton->setVisible(true);

    tempFiliname.assign(fileName);
}

void Intrinsic::calibrateCamera()
{
    numPhoto=ui->numPicsDropdown->value();
    counter=0;
    cout <<" Photos to be taken :"<< numPhoto<<endl;

    ui->cameraChosen->setText( ui->cameraDropdown->currentText());
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
    cout << "Photo number "<< counter<<" saved"<<endl;
    ui->saveImage->setVisible(false);
    ui->saveImageButton->setVisible(false);
    ui->discardImageButton->setVisible(false);
    ui->pictureButton->setVisible(true);
    ui->imageProgressBar->setValue( counter );

    if(counter==numPhoto)
    {
        ui->cameraDropdown->setVisible(true);
        ui->cameraChosen->setVisible(false);
        ui->infoCalibration->setVisible(true);

        //CORRER ROTINA DE CALIBRAÇÃO
        //intrinsic_compute i
        //error = i.run(nr_imagens, img_folder, img_filename)
        //este filename pode ser o IP ou assim?

    }
}

void Intrinsic::on_discardImageButton_clicked()
{
    ui->saveImage->setVisible(false);
    ui->saveImageButton->setVisible(false);
    ui->discardImageButton->setVisible(false);
    ui->pictureButton->setVisible(true);
    std::remove(tempFiliname.c_str());
}

void Intrinsic::on_cancelCalibrationButton_clicked()
{
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
