/********************************************************************************
** Form generated from reading UI file 'realtimetracking.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMETRACKING_H
#define UI_REALTIMETRACKING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RealTimeTracking
{
public:
    QPushButton *stopRec_pushButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *RandomizeButton;

    void setupUi(QDialog *RealTimeTracking)
    {
        if (RealTimeTracking->objectName().isEmpty())
            RealTimeTracking->setObjectName(QString::fromUtf8("RealTimeTracking"));
        RealTimeTracking->resize(895, 516);
        stopRec_pushButton = new QPushButton(RealTimeTracking);
        stopRec_pushButton->setObjectName(QString::fromUtf8("stopRec_pushButton"));
        stopRec_pushButton->setGeometry(QRect(730, 400, 151, 25));
        gridLayoutWidget = new QWidget(RealTimeTracking);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 20, 681, 461));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        RandomizeButton = new QPushButton(RealTimeTracking);
        RandomizeButton->setObjectName(QString::fromUtf8("RandomizeButton"));
        RandomizeButton->setGeometry(QRect(730, 350, 151, 25));

        retranslateUi(RealTimeTracking);

        QMetaObject::connectSlotsByName(RealTimeTracking);
    } // setupUi

    void retranslateUi(QDialog *RealTimeTracking)
    {
        RealTimeTracking->setWindowTitle(QApplication::translate("RealTimeTracking", "Dialog", nullptr));
        stopRec_pushButton->setText(QApplication::translate("RealTimeTracking", "Stop recording", nullptr));
        RandomizeButton->setText(QApplication::translate("RealTimeTracking", "Randomize Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RealTimeTracking: public Ui_RealTimeTracking {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMETRACKING_H
