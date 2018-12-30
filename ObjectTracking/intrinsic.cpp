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
    for (uint i = 0; i<listOfCameras.size();i++ )
    {
        Camera cam = listOfCameras[i];
        ui->cameraDropdown->addItem(QString::fromStdString(cam.getName()));
    }
    ui->verticalSlider->setVisible(false);
    ui->pictureButton->setVisible(false);
    ui->numPicsDropdown->setValue(30);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->saveButton->setVisible(false);
    ui->repeatButton->setVisible(false);
    //QPixmap pix;
    //ui->label_CameraFeed->setPixmap(pix.scaled(420, 280, Qt::KeepAspectRatio));
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
    counter = counter + 1;
    //take picture with open cv, save the picture to %foldername%
    //check if images are corrupt?
    ui->verticalSlider->setValue(counter);

    if  (counter == ui->verticalSlider->maximum())
    {
        double errorVal = 10.3243;

        //end of picture-taking phase
        ui->pictureButton->setVisible(false);
        ui->verticalSlider->setValue(0);

        //errorVal = intrinsic_compute::run(); //compute intrinsic calibration for a single camera

        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_4->setText(QString::fromStdString(to_string(errorVal)));
        ui->saveButton->setVisible(true);
        ui->repeatButton->setVisible(true);
    }

}

void Intrinsic::calibrateCamera()
{
    // calibrate camera is misleading - actually starts a picture-taking routine for future calibration

    /*
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->saveButton->setVisible(false);
    ui->repeatButton->setVisible(false);
    int numOfPic = ui->numPicsDropdown->value();
    uint i = ui->cameraDropdown->currentIndex();
    Camera cam = listOfCameras[i];
    counter = 0;

    //open camera frame with open cv
    ui->verticalSlider->setVisible(true);
    ui->verticalSlider->setMaximum(numOfPic);
    ui->pictureButton->setVisible(true);
    */
    cout << "AAAAAAAAAAAAAAAAA" << endl;
    // Get camera index from the dropdown menu
    //int cameraIndex = ui->cameraDropdown->currentIndex();
    //string ip = listOfCameras[cameraIndex].getIP();

    // Get number of pictures required
    //int numOfPic = ui->numPicsDropdown->value();
    // Show live feed
    string fileName;
    cout << "0000000000000" << endl;
    FlyCapture2::IPAddress ipa = 2852045226;
    for (int i = 0; i < 10; i++)
    {
      //  cout << "11111111111111" << endl;
        fileName = takeSinglePictureFromSingleCamera(ipa);
    //    cout << "fileName" << fileName << endl;
        QImage myImage;
        myImage.load(QString::fromStdString(fileName),"png");

        ui->label_CameraFeed->setPixmap(QPixmap::fromImage(myImage).scaled(420,280,Qt::KeepAspectRatio));
        ui->label_CameraFeed->repaint();
     //   cout << "44444444444444" << endl;
    }
    // string fileName = takeSinglePictureFromSingleCamera(0);
    //QPixmap pix(QString::fromStdString(fileName));
    //ui->label_CameraFeed->setPixmap(pix.scaled(420, 280, Qt::KeepAspectRatio));


    // Loop over the number of pictures required (default is 30)
        // In each iteration:
            // Show the picture on the labelPic component
            // Increase the slider count by 1
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
