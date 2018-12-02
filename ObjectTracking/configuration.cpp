#include "configuration.h"
#include "ui_configuration.h"
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
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setText(tr("Attempt"));
    item->setFlags(Qt::ItemIsSelectable);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, item);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(tr("Remove"));
    item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 5, item2);
}

void Configuration::on_tableWidget_cellClicked(int row, int column)
{
    if (column == 4) {

        //if attempt comunication
        string camName = ui->tableWidget->item(row,0)->text().toStdString();
        string camIP = ui->tableWidget->item(row, 1)->text().toStdString();
        string camPos = ui->tableWidget->item(row,2)->text().toStdString();
        string xstring = camPos.substr(0, camPos.find(","));
        camPos = camPos.substr(camPos.find(",")+1);
        string ystring = camPos.substr(0, camPos.find(","));
        string zstring = camPos.substr(camPos.find(",")+1);
        string anglestring = ui->tableWidget->item(row,3)->text().toStdString();
        float x = stof(xstring);
        float y = stof(ystring);
        float z = stof(zstring);
        float angle = stof(anglestring);
        Camera newCamera(camName, camIP, x, y, z, angle);
        listOfCameras.push_back(newCamera);
        QColor green(0,255,0);
        ui->tableWidget->item(row,4)->setBackgroundColor(green);
    }
    else {
        if (column == 5) {
            ui->tableWidget->removeRow(row);/*
            if (listOfCameras.size()==row+1)
                listOfCameras.;
*/
        }
    }
}

vector<Camera> Configuration::getListOfCameras()
{
    return listOfCameras;
}
