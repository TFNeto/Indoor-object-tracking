#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QDataStream>

#include <iostream>
#include <sstream>

#include "configuration.h"
#include "ui_configuration.h"
#include "global.h"

#include "camerafly.h"

//#include "stdafx.h"
//#include "FlyCapture2.h"

//using namespace FlyCapture2;
using namespace std;

Configuration::Configuration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configuration)
{
    ui->setupUi(this);
}

Configuration::~Configuration()
{
    delete ui;
}

void Configuration::on_close_pushButton_clicked()
{
    this->close();
}

void Configuration::on_addCam_push_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    QTableWidgetItem *item0 = new QTableWidgetItem;
    item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, item0);
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, item1);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, item2);
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, item3);
    QTableWidgetItem *item4 = new QTableWidgetItem;
    item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, item4);
    QTableWidgetItem *item5 = new QTableWidgetItem;
    item5->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 5, item5);
    QTableWidgetItem *item6 = new QTableWidgetItem;
    item6->setText(tr("Attempt"));
    item6->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 6, item6);
    QTableWidgetItem *item7 = new QTableWidgetItem;
    item7->setText(tr("Remove"));
    item7->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 7, item7);
}

void Configuration::on_tableWidget_cellClicked(int row, int column)
{
    QColor green(0,255,0);
    if (column == 6)
    {
        //if attempt comunication
        string camName = ui->tableWidget->item(row,0)->text().toStdString();
        string camIP = ui->tableWidget->item(row, 1)->text().toStdString();
        string xstring = ui->tableWidget->item(row,2)->text().toStdString();
        string ystring = ui->tableWidget->item(row,3)->text().toStdString();
        string zstring =  ui->tableWidget->item(row,4)->text().toStdString();
        string anglestring = ui->tableWidget->item(row,5)->text().toStdString();
        float x = stof(xstring);
        float y = stof(ystring);
        float z = stof(zstring);
        float angle = stof(anglestring);
        Camera newCamera(camName, camIP, x, y, z, angle);
        listOfCameras.push_back(newCamera);
        ui->tableWidget->item(row,6)->setBackgroundColor(green);
    }
    else if (column == 7)
    {
        if (ui->tableWidget->item(row, 6)->backgroundColor() == green)
        {
            QMessageBox::critical(this, tr("Error"), tr("Camera cannot be removed because connnection is already established."));
        }
        else
        {
            ui->tableWidget->removeRow(row);
        }
    }
}

void Configuration::on_saveCon_push_clicked()
{
}

void Configuration::on_loadCon_push_clicked()
{
}

void Configuration::updateTable(vector<Camera> newListOfCameras)
{
    // Set number of table row's
    ui->tableWidget->setRowCount(static_cast<int>(newListOfCameras.size()));

    for (size_t i = 0; i < newListOfCameras.size(); i++)
    {
        // Create a camera object, so we can access its methods
        Camera camObj = newListOfCameras[i];

        // Set name
        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(QString::fromStdString(camObj.getName()));
        name->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableWidget->setItem(static_cast<int>(i), 0, name);
        // Set IP Address
        QTableWidgetItem *ip = new QTableWidgetItem;
        ip->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ip->setText(QString::fromStdString(camObj.getIP()));
        ui->tableWidget->setItem(static_cast<int>(i), 1, ip);
        // Set position X
        QTableWidgetItem *positionX = new QTableWidgetItem;
        positionX->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        positionX->setText(QString::fromStdString(to_string(camObj.getX())));
        ui->tableWidget->setItem(static_cast<int>(i), 2, positionX);
        // Set position Y
        QTableWidgetItem *positionY = new QTableWidgetItem;
        positionY->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        positionY->setText(QString::fromStdString(to_string(camObj.getY())));
        ui->tableWidget->setItem(static_cast<int>(i), 3, positionY);
        // Set position Z
        QTableWidgetItem *positionZ = new QTableWidgetItem;
        positionZ->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        positionZ->setText(QString::fromStdString(to_string(camObj.getZ())));
        ui->tableWidget->setItem(static_cast<int>(i), 4, positionZ);
        // Set angle
        QTableWidgetItem *angle = new QTableWidgetItem;
        angle->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        angle->setText(QString::fromStdString(to_string(camObj.getAngle())));
        ui->tableWidget->setItem(static_cast<int>(i), 5, angle);
        // Connection - attempt
        QTableWidgetItem *connectionAttempt = new QTableWidgetItem;
        connectionAttempt->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        connectionAttempt->setText(tr("Attempt"));
        ui->tableWidget->setItem(static_cast<int>(i), 6, connectionAttempt);
        // Connection - remove
        QTableWidgetItem *connectionRemove = new QTableWidgetItem;
        connectionRemove->setText(tr("Remove"));
        connectionRemove->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableWidget->setItem(static_cast<int>(i), 7, connectionRemove);
    }
}

void Configuration::on_scan_push_clicked()
{
    // Clear list of cameras before scanning, to avoid duplication
    // listOfCameras.clear();
    listOfCameras = scanCameras();
    this->updateTable(listOfCameras);
}
