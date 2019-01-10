#include "realtimetracking.h"
#include "ui_realtimetracking.h"

RealTimeTracking::RealTimeTracking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RealTimeTracking)
{
    graph = new QtDataVisualization::Q3DScatter;
    container = QWidget::createWindowContainer(graph);
    modifier = new ScatterDataModifier(graph);
    modifier->addData();
    ui->setupUi(this);
    ui->gridLayout->addWidget(container);
    ui->stopRec_pushButton->setVisible(false);
    //ui->startRec_pushButton->setVisible(true);
}

RealTimeTracking::~RealTimeTracking()
{
    delete ui;
}

void RealTimeTracking::on_RandomizeButton_clicked()
{
    modifier->addData();
}

void RealTimeTracking::on_startRec_pushButton_clicked()
{
    ui->stopRec_pushButton->setVisible(true);
    ui->startRec_pushButton->setVisible(false);
}

void RealTimeTracking::on_stopRec_pushButton_clicked()
{
    ui->stopRec_pushButton->setVisible(false);
    ui->startRec_pushButton->setVisible(true);
}
