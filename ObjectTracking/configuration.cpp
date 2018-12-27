#include "configuration.h"
#include "ui_configuration.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QDataStream>
#include "iostream"
#include "global.h"

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
    else
    {
        if (column == 7)
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
}

void Configuration::on_saveCon_push_clicked()
{
}

void Configuration::on_loadCon_push_clicked()
{
}

void Configuration::updateTable(vector<Camera> newListOfCameras){
    while (ui->tableWidget->rowCount() > 0)
        ui->tableWidget->removeRow(0);

    for (uint i = 0; i<newListOfCameras.size(); i++ )
    {
        Camera cam = newListOfCameras[i];
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
        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item4->setText(tr("Attempt"));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, item4);
        QTableWidgetItem *item5 = new QTableWidgetItem;
        item5->setText(tr("Remove"));
        item5->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 5, item5);
    }
}
