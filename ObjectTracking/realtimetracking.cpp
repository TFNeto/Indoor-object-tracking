#include "realtimetracking.h"
#include "ui_realtimetracking.h"

RealTimeTracking::RealTimeTracking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RealTimeTracking)
{
    ui->setupUi(this);
}

RealTimeTracking::~RealTimeTracking()
{
    delete ui;
}
