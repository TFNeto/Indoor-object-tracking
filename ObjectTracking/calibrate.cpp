#include <string>
#include "calibrate.h"
#include "ui_calibrate.h"
#include "global.h"
#include "intrinsic.h"
#include "extrinsic.h"
#include "intrinsic_compute.h"
#include "extrinsic_compute.h"
#include <QMessageBox>

using namespace std;

Calibrate::Calibrate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calibrate)
{
    ui->setupUi(this);
}

Calibrate::~Calibrate()
{
    delete ui;
}

void Calibrate::on_close_button_clicked()
{
    this->close();
}

void Calibrate::setCameraInfo()
{
    // Set number of table row's
    ui->tableWidget->setRowCount(static_cast<int>(listOfCameras.size()));

    for (size_t i = 0; i < listOfCameras.size(); i++)
    {
        // Set name
        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(QString::fromStdString(listOfCameras[i].getName()));
        name->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableWidget->setItem(static_cast<int>(i), 0, name);
        // Set IP Address
        QTableWidgetItem *ip = new QTableWidgetItem;
        ip->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ip->setText(QString::fromStdString(listOfCameras[i].getIP()));
        ui->tableWidget->setItem(static_cast<int>(i), 1, ip);
        // Set position X
        QTableWidgetItem *position = new QTableWidgetItem;
        position->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        position->setText(QString::fromStdString(to_string(listOfCameras[i].getX()) + ", " + to_string(listOfCameras[i].getY()) + ", " + to_string(listOfCameras[i].getZ())));
        ui->tableWidget->setItem(static_cast<int>(i), 2, position);
        // Set angle
        QTableWidgetItem *angle = new QTableWidgetItem;
        angle->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        angle->setText(QString::fromStdString(to_string(listOfCameras[i].getAngle())));
        ui->tableWidget->setItem(static_cast<int>(i), 5, angle);
        // Edit
        QTableWidgetItem *edit = new QTableWidgetItem;
        edit->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        edit->setText(tr("Edit"));
        ui->tableWidget->setItem(static_cast<int>(i), 4, edit);
    }
}

void Calibrate::on_intrinsicButton_clicked()
{
    Intrinsic intrinsicWindow;
    intrinsicWindow.setModal(true);
    intrinsicWindow.exec();
}

void Calibrate::on_extrinsicButton_clicked()
{

    /*for (uint i = 0; i<listOfCameras.size();i++ )
    {
        if(!listOfCameras[i].isIntrinsicCalibrated())
        {
            QMessageBox::critical(this, tr("Error"), tr("All cameras must be intrinsic calibrated"));
            return;
        }
    }
*/

    extrinsic extrinsicWindow;
    extrinsicWindow.setModal(true);
    extrinsicWindow.exec();
}
