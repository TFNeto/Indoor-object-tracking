#ifndef REALTIMETRACKING_H
#define REALTIMETRACKING_H

#include <QDialog>
#include "scatterdatamodifier.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QSize>
#include <QMessageBox>
#include <QtGui/QScreen>

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

private:
    Ui::RealTimeTracking *ui;


    QtDataVisualization::Q3DScatter * graph;
    ScatterDataModifier *modifier;
    QWidget *container;
};

#endif // REALTIMETRACKING_H
