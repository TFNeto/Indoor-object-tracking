#include "trackinglog.h"
#include "ui_trackinglog.h"
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dseries.h>

TrackingLog::TrackingLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackingLog)
{

    ui->setupUi(this);
}

TrackingLog::~TrackingLog()
{
    delete ui;
}

void TrackingLog::on_close_pushButton_clicked()
{
    this->close();
}
