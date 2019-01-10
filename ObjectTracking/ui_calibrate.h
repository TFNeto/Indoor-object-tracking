/********************************************************************************
** Form generated from reading UI file 'calibrate.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATE_H
#define UI_CALIBRATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Calibrate
{
public:
    QTableWidget *tableWidget;
    QPushButton *extrinsicButton;
    QPushButton *close_button;
    QPushButton *intrinsicButton;

    void setupUi(QDialog *Calibrate)
    {
        if (Calibrate->objectName().isEmpty())
            Calibrate->setObjectName(QString::fromUtf8("Calibrate"));
        Calibrate->resize(887, 572);
        tableWidget = new QTableWidget(Calibrate);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem3->setFont(font);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 20, 721, 381));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(180);
        extrinsicButton = new QPushButton(Calibrate);
        extrinsicButton->setObjectName(QString::fromUtf8("extrinsicButton"));
        extrinsicButton->setGeometry(QRect(460, 480, 231, 25));
        close_button = new QPushButton(Calibrate);
        close_button->setObjectName(QString::fromUtf8("close_button"));
        close_button->setGeometry(QRect(720, 480, 121, 25));
        intrinsicButton = new QPushButton(Calibrate);
        intrinsicButton->setObjectName(QString::fromUtf8("intrinsicButton"));
        intrinsicButton->setGeometry(QRect(210, 480, 221, 25));

        retranslateUi(Calibrate);

        QMetaObject::connectSlotsByName(Calibrate);
    } // setupUi

    void retranslateUi(QDialog *Calibrate)
    {
        Calibrate->setWindowTitle(QApplication::translate("Calibrate", "Calibrate the cameras", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Calibrate", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Calibrate", "IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Calibrate", "Physical Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Calibrate", "Pointing Direction", nullptr));
        extrinsicButton->setText(QApplication::translate("Calibrate", "Start extrinsic calibration", nullptr));
        close_button->setText(QApplication::translate("Calibrate", "Close", nullptr));
        intrinsicButton->setText(QApplication::translate("Calibrate", "Start intrinsic calibration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calibrate: public Ui_Calibrate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATE_H
