#ifndef REALTIMETRACKING_H
#define REALTIMETRACKING_H

#include <QDialog>
#include "scatterdatamodifier.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QSize>
#include <QMessageBox>
#include <QtGui/QScreen>
#include <thread>

namespace Ui {
class RealTimeTracking;
}

class RealTimeTracking : public QDialog
{
    Q_OBJECT

public:
    explicit RealTimeTracking(QWidget *parent = nullptr);
    ~RealTimeTracking();

private slots:
    void on_RandomizeButton_clicked();

    void on_startRec_pushButton_clicked();

    void on_stopRec_pushButton_clicked();

private:
    Ui::RealTimeTracking *ui;
    QtDataVisualization::Q3DScatter * graph;
    ScatterDataModifier *modifier;
    QWidget *container;
    std::vector<std::thread> tvec;
};

#endif // REALTIMETRACKING_H
