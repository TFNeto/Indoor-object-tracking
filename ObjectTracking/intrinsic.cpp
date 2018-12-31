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
    ui->lcdNumPhotos->setVisible(false);
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

    if  (counter == ui->verticalSlider->maximum())
    {
        intrinsic_compute i;
        double errorVal = 1;

        //end of picture-taking phase
        ui->pictureButton->setVisible(false);
        ui->verticalSlider->setValue(0);

        //test vars
        int counter = 27; //overriding for tests
        string imgs_directory = "../intrinsic_right";
        string imgs_filename = "right";

        errorVal = i.run(counter, imgs_directory, imgs_filename); //compute intrinsic calibration for a single camera

        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_4->setText(QString::fromStdString(to_string(errorVal)));
        ui->saveButton->setVisible(true);
        ui->repeatButton->setVisible(true);
    }

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

   // tempFiliname.assign(fileName);
}

void Intrinsic::calibrateCamera()
{
    numPhoto=ui->numPicsDropdown->value();
    cout <<" Photos to be taken :"<< numPhoto<<endl;
    ui->startCalibrButton->setVisible(false);
    ui->numPicsDropdown->setVisible(false);
    ui->lcdNumPhotos->display(numPhoto);
    ui->lcdNumPhotos->setVisible(true);
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
    cout <<"Photo number "<< counter<<" saved"<<endl;
    ui->saveImage->setVisible(false);
    ui->saveImageButton->setVisible(false);
    ui->discardImageButton->setVisible(false);
    ui->pictureButton->setVisible(true);
    ui->imageProgressBar->setValue( (int) ( (float)counter/(float)numPhoto*100 ) );
    /*
    if(counter==numPhoto)
    {
       //função para calibração intrinseca
    }*/
}

void Intrinsic::on_discardImageButton_clicked()
{
    ui->saveImage->setVisible(false);
    ui->saveImageButton->setVisible(false);
    ui->discardImageButton->setVisible(false);
    ui->pictureButton->setVisible(true);
  //  std::remove(tempFiliname.c_str());
}

