/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *start_pushButton;
    QPushButton *configure_pushButton;
    QPushButton *calibrate_pushButton;
    QPushButton *log_pushButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(940, 578);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        start_pushButton = new QPushButton(centralWidget);
        start_pushButton->setObjectName(QString::fromUtf8("start_pushButton"));
        start_pushButton->setGeometry(QRect(280, 40, 381, 101));
        configure_pushButton = new QPushButton(centralWidget);
        configure_pushButton->setObjectName(QString::fromUtf8("configure_pushButton"));
        configure_pushButton->setGeometry(QRect(280, 160, 381, 101));
        calibrate_pushButton = new QPushButton(centralWidget);
        calibrate_pushButton->setObjectName(QString::fromUtf8("calibrate_pushButton"));
        calibrate_pushButton->setGeometry(QRect(280, 280, 381, 91));
        log_pushButton = new QPushButton(centralWidget);
        log_pushButton->setObjectName(QString::fromUtf8("log_pushButton"));
        log_pushButton->setGeometry(QRect(280, 390, 381, 91));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        start_pushButton->setText(QApplication::translate("MainWindow", "Start", nullptr));
        configure_pushButton->setText(QApplication::translate("MainWindow", "Configure", nullptr));
        calibrate_pushButton->setText(QApplication::translate("MainWindow", "Calibrate", nullptr));
        log_pushButton->setText(QApplication::translate("MainWindow", "Log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
