#include <string>
#include "calibrate.h"
#include "ui_calibrate.h"
#include "global.h"
#include "intrinsic.h"
#include "extrinsic.h"
#include "intrinsic_compute.h"

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

void Calibrate::setCameraInfo(vector<Camera> listOfCameras)
{
    // Set number of table row's
    ui->tableWidget->setRowCount(static_cast<int>(listOfCameras.size()));

    for (size_t i = 0; i < listOfCameras.size(); i++)
    {
        // Create a camera object, so we can access its methods
        Camera camObj = listOfCameras[i];

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
        QTableWidgetItem *position = new QTableWidgetItem;
        position->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        position->setText(QString::fromStdString(to_string(camObj.getX()) + ", " + to_string(camObj.getY()) + ", " + to_string(camObj.getZ())));
        ui->tableWidget->setItem(static_cast<int>(i), 2, position);
        // Set angle
        QTableWidgetItem *angle = new QTableWidgetItem;
        angle->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        angle->setText(QString::fromStdString(to_string(camObj.getAngle())));
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
    /*Intrinsic intrinsicWindow;
    intrinsicWindow.setModal(true);
    intrinsicWindow.exec();*/

    intrinsic_compute i;
    double errorVal = 1;

    //test vars
    int counter = 27; //overriding for tests
    string imgs_directory = "../intrinsic_right";
    string imgs_filename = "right";

    //função para calibração intrinseca abaixo//
cout << "pepe\n";
    errorVal = i.run(counter, imgs_directory, imgs_filename); //compute intrinsic calibration for a single camera
}

void Calibrate::on_extrinsicButton_clicked()
{
    extrinsic extrinsicWindow;
    extrinsicWindow.setModal(true);
    extrinsicWindow.exec();
}
