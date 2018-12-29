#include "extrinsic.h"
#include "ui_extrinsic.h"
#include "global.h"
#include <string>

using namespace std;

int count = 0;
Camera cam1;
Camera cam2;

extrinsic::extrinsic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::extrinsic)
{
    ui->setupUi(this);
    for (uint i = 0; i<listOfCameras.size();i++ )
    {
        Camera cam = listOfCameras[i];
        ui->comboBox->addItem(QString::fromStdString(cam.getName()));
    }
    ui->comboBox->setCurrentIndex(0);
    for (uint i = 1; i<listOfCameras.size();i++ )
    {
        Camera cam = listOfCameras[i];
        ui->comboBox_2->addItem(QString::fromStdString(cam.getName()));
    }
    ui->verticalSlider->setVisible(false);
    ui->numPicsDropdown->setValue(30);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
}

extrinsic::~extrinsic()
{
    delete ui;
}

void extrinsic::on_closeButton_clicked()
{
    this->close();
}

void extrinsic::on_cameraDropdown_currentIndexChanged(int index)
{
    ui->comboBox_2->clear();
    for (uint i = 0; i < listOfCameras.size(); i++)
    {
        int j = i;
        if (j != index)
        {
            Camera cam = listOfCameras[i];
            ui->comboBox_2->addItem(QString::fromStdString(cam.getName()));
        }
    }
    cam1 = listOfCameras[index];
}

void extrinsic::on_calibrateButton_clicked()
{
    calibrateCameraPair();
}

void extrinsic::on_comboBox_2_currentIndexChanged()
{
    for (uint i = 0; i<listOfCameras.size();i++ )
    {
        QString name = ui->comboBox_2->currentText();
        if (QString::compare(QString::fromStdString(listOfCameras[i].getName()), name))
        {
            cam2 = listOfCameras[i];
        }
    }
}

void extrinsic::calibrateCameraPair()
{
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    int numOfPic = ui->numPicsDropdown->value();

    // open cameras
    ui->verticalSlider->setVisible(true);
    ui->verticalSlider->setMaximum(numOfPic);

    //do the calibration
}
