/********************************************************************************
** Form generated from reading UI file 'trackinglog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKINGLOG_H
#define UI_TRACKINGLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackingLog
{
public:
    QGraphicsView *graphicsView;
    QTableWidget *objectData;
    QTableWidget *tableWidget;
    QPushButton *close_pushButton;

    void setupUi(QDialog *TrackingLog)
    {
        if (TrackingLog->objectName().isEmpty())
            TrackingLog->setObjectName(QString::fromUtf8("TrackingLog"));
        TrackingLog->resize(849, 539);
        graphicsView = new QGraphicsView(TrackingLog);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(20, 20, 521, 401));
        objectData = new QTableWidget(TrackingLog);
        if (objectData->columnCount() < 1)
            objectData->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        objectData->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (objectData->rowCount() < 4)
            objectData->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        objectData->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        objectData->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        objectData->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        objectData->setVerticalHeaderItem(3, __qtablewidgetitem4);
        objectData->setObjectName(QString::fromUtf8("objectData"));
        objectData->setGeometry(QRect(560, 190, 241, 192));
        objectData->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget = new QTableWidget(TrackingLog);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(560, 40, 241, 121));
        tableWidget->horizontalHeader()->setDefaultSectionSize(150);
        tableWidget->verticalHeader()->setDefaultSectionSize(100);
        close_pushButton = new QPushButton(TrackingLog);
        close_pushButton->setObjectName(QString::fromUtf8("close_pushButton"));
        close_pushButton->setGeometry(QRect(630, 460, 171, 41));

        retranslateUi(TrackingLog);

        QMetaObject::connectSlotsByName(TrackingLog);
    } // setupUi

    void retranslateUi(QDialog *TrackingLog)
    {
        TrackingLog->setWindowTitle(QApplication::translate("TrackingLog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = objectData->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TrackingLog", "Object Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = objectData->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("TrackingLog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = objectData->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("TrackingLog", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = objectData->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("TrackingLog", "Physical Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = objectData->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("TrackingLog", "Angle", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("TrackingLog", "Date and time", nullptr));
        close_pushButton->setText(QApplication::translate("TrackingLog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrackingLog: public Ui_TrackingLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKINGLOG_H
