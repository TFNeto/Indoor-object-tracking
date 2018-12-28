#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QDataStream>

#include <iomanip>
#include <iostream>
#include <sstream>

#include "configuration.h"
#include "ui_configuration.h"
#include "global.h"

#include "stdafx.h"
#include "FlyCapture2.h"

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

void PrintError(FlyCapture2::Error error) { error.PrintErrorTrace(); }

void PrintCameraInfo(FlyCapture2::CameraInfo *pCamInfo)
{
    ostringstream macAddress;
    macAddress << hex << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[0]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[1]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[2]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[3]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[4]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[5]);

    ostringstream ipAddress;
    ipAddress << static_cast<unsigned int>(pCamInfo->ipAddress.octets[0]) << "."
              << static_cast<unsigned int>(pCamInfo->ipAddress.octets[1]) << "."
              << static_cast<unsigned int>(pCamInfo->ipAddress.octets[2]) << "."
              << static_cast<unsigned int>(pCamInfo->ipAddress.octets[3]);

    ostringstream subnetMask;
    subnetMask << static_cast<unsigned int>(pCamInfo->subnetMask.octets[0]) << "."
               << static_cast<unsigned int>(pCamInfo->subnetMask.octets[1]) << "."
               << static_cast<unsigned int>(pCamInfo->subnetMask.octets[2]) << "."
               << static_cast<unsigned int>(pCamInfo->subnetMask.octets[3]);

    ostringstream defaultGateway;
    defaultGateway << static_cast<unsigned int>(pCamInfo->defaultGateway.octets[0]) << "."
                   << static_cast<unsigned int>(pCamInfo->defaultGateway.octets[1]) << "."
                   << static_cast<unsigned int>(pCamInfo->defaultGateway.octets[2]) << "."
                   << static_cast<unsigned int>(pCamInfo->defaultGateway.octets[3]);

    cout << endl;
    cout << "*** CAMERA INFORMATION ***" << endl;
    cout << "Serial number - " << pCamInfo->serialNumber << endl;
    cout << "Camera model - " << pCamInfo->modelName << endl;
    cout << "Camera vendor - " << pCamInfo->vendorName << endl;
    cout << "Sensor - " << pCamInfo->sensorInfo << endl;
    cout << "Resolution - " << pCamInfo->sensorResolution << endl;
    cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
    cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl;
    cout << "GigE version - " << pCamInfo->gigEMajorVersion << "."
         << pCamInfo->gigEMinorVersion << endl;
    cout << "User defined name - " << pCamInfo->userDefinedName << endl;
    cout << "XML URL 1 - " << pCamInfo->xmlURL1 << endl;
    cout << "XML URL 2 - " << pCamInfo->xmlURL2 << endl;
    cout << "MAC address - " << macAddress.str() << endl;
    cout << "IP address - " << ipAddress.str() << endl;
    cout << "Subnet mask - " << subnetMask.str() << endl;
    cout << "Default gateway - " << defaultGateway.str() << endl << endl;
    listOfCameras.push_back(Camera(pCamInfo->modelName, ipAddress.str(), 0, 0, 0, 0));
}

void Configuration::on_scan_push_clicked()
{
    // Clear list of cameras before scanning, to avoid duplication
    listOfCameras.clear();

    // TODO: Move the code below to a function ?
    FlyCapture2::Error error;
    FlyCapture2::BusManager busMgr;

    FlyCapture2::CameraInfo camInfo[10];
    unsigned int numCamInfo = 10;
    error = FlyCapture2::BusManager::DiscoverGigECameras(camInfo, &numCamInfo);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return;
    }

    cout << "DEBUG: Number of GigE cameras discovered: " << numCamInfo << endl;

    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        PrintCameraInfo(&camInfo[i]);
    }

    // No cameras found
    if (numCamInfo == 0)
    {
        // TODO: Show error message
        cout << "No suitable GigE cameras found. Press Enter to exit..."
             << endl;
        cin.ignore();
    } else {
        this->updateTable(listOfCameras);
    }
}
