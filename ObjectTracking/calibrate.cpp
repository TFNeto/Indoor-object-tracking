#include "calibrate.h"
#include "ui_calibrate.h"
#include <string>
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
    ui->tableWidget->setRowCount(listOfCameras.size());
    for (uint i = 0; i<listOfCameras.size();i++ ){
        Camera cam = listOfCameras[i];
        QTableWidgetItem *item0 = new QTableWidgetItem;
        item0->setText(QString::fromStdString( cam.getName()));
        item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableWidget->setItem(i, 0, item0);
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item1->setText(QString::fromStdString(cam.getIP()));
        ui->tableWidget->setItem(i, 1, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item2->setText(QString::fromStdString(to_string(cam.getX()) + ", " + to_string(cam.getY()) + ", " + to_string(cam.getZ())));
        ui->tableWidget->setItem(i, 2, item2);
        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item3->setText(QString::fromStdString(to_string(cam.getAngle())));
        ui->tableWidget->setItem(i, 3, item3);

    }
}

void Calibrate::on_pushButton_clicked()
{

}
