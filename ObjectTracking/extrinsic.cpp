#include "extrinsic.h"
#include "ui_extrinsic.h"
#include "global.h"
#include <string>
#include <iostream>

using namespace std;

int count = 0;
Camera camera1;
Camera camera2;

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
}

extrinsic::~extrinsic()
{
    delete ui;
}

void extrinsic::on_closeButton_clicked()
{
    this->close();
}

void extrinsic::on_calibrateButton_clicked()
{
    if(ui->comboBox->currentIndex()!=ui->comboBox_2->currentIndex())
    {
        camera1 = listOfCameras[ui->comboBox->currentIndex()];
        camera2 = listOfCameras[ui->comboBox_2->currentIndex()];
        cout <<"DEBUG Selected camera with Ip : "<<camera1.getIP()<<endl;
        cout <<"DEBUG Selected camera with IP : "<<camera2.getIP()<<endl;
        ui->errorText->setVisible(false);
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
