/********************************************************************************
** Form generated from reading UI file 'intrinsic.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTRINSIC_H
#define UI_INTRINSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Intrinsic
{
public:
    QComboBox *cameraDropdown;
    QLabel *labelSelectCam;
    QLabel *labelNumberPhoto;
    QSpinBox *numPicsDropdown;
    QPushButton *startCalibrButton;
    QPushButton *closeButton;
    QPushButton *pictureButton;
    QLabel *labelCalibrationError;
    QPushButton *repeatButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QLabel *label_CameraFeed;
    QLabel *saveImage;
    QPushButton *saveImageButton;
    QPushButton *discardImageButton;
    QProgressBar *imageProgressBar;
    QLabel *numPics;
    QPushButton *cancelCalibrationButton;
    QLabel *cameraChosen;
    QTextBrowser *infoCalibration;

    void setupUi(QDialog *Intrinsic)
    {
        if (Intrinsic->objectName().isEmpty())
            Intrinsic->setObjectName(QString::fromUtf8("Intrinsic"));
        Intrinsic->resize(1000, 650);
        Intrinsic->setMouseTracking(false);
        Intrinsic->setSizeGripEnabled(false);
        Intrinsic->setModal(false);
        cameraDropdown = new QComboBox(Intrinsic);
        cameraDropdown->setObjectName(QString::fromUtf8("cameraDropdown"));
        cameraDropdown->setGeometry(QRect(230, 30, 391, 25));
        labelSelectCam = new QLabel(Intrinsic);
        labelSelectCam->setObjectName(QString::fromUtf8("labelSelectCam"));
        labelSelectCam->setGeometry(QRect(40, 30, 181, 20));
        QFont font;
        font.setPointSize(14);
        labelSelectCam->setFont(font);
        labelSelectCam->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        labelNumberPhoto = new QLabel(Intrinsic);
        labelNumberPhoto->setObjectName(QString::fromUtf8("labelNumberPhoto"));
        labelNumberPhoto->setGeometry(QRect(690, 30, 181, 17));
        labelNumberPhoto->setFont(font);
        numPicsDropdown = new QSpinBox(Intrinsic);
        numPicsDropdown->setObjectName(QString::fromUtf8("numPicsDropdown"));
        numPicsDropdown->setGeometry(QRect(880, 30, 48, 26));
        numPicsDropdown->setMinimum(1);
        numPicsDropdown->setMaximum(100);
        startCalibrButton = new QPushButton(Intrinsic);
        startCalibrButton->setObjectName(QString::fromUtf8("startCalibrButton"));
        startCalibrButton->setGeometry(QRect(730, 80, 151, 25));
        closeButton = new QPushButton(Intrinsic);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(800, 460, 89, 25));
        pictureButton = new QPushButton(Intrinsic);
        pictureButton->setObjectName(QString::fromUtf8("pictureButton"));
        pictureButton->setGeometry(QRect(270, 600, 201, 25));
        labelCalibrationError = new QLabel(Intrinsic);
        labelCalibrationError->setObjectName(QString::fromUtf8("labelCalibrationError"));
        labelCalibrationError->setGeometry(QRect(790, 200, 121, 17));
        repeatButton = new QPushButton(Intrinsic);
        repeatButton->setObjectName(QString::fromUtf8("repeatButton"));
        repeatButton->setGeometry(QRect(800, 270, 89, 25));
        saveButton = new QPushButton(Intrinsic);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(800, 320, 89, 25));
        loadButton = new QPushButton(Intrinsic);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(800, 370, 89, 25));
        label_CameraFeed = new QLabel(Intrinsic);
        label_CameraFeed->setObjectName(QString::fromUtf8("label_CameraFeed"));
        label_CameraFeed->setGeometry(QRect(70, 140, 630, 420));
        saveImage = new QLabel(Intrinsic);
        saveImage->setObjectName(QString::fromUtf8("saveImage"));
        saveImage->setGeometry(QRect(110, 600, 181, 20));
        saveImage->setFont(font);
        saveImage->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        saveImageButton = new QPushButton(Intrinsic);
        saveImageButton->setObjectName(QString::fromUtf8("saveImageButton"));
        saveImageButton->setGeometry(QRect(270, 600, 89, 25));
        discardImageButton = new QPushButton(Intrinsic);
        discardImageButton->setObjectName(QString::fromUtf8("discardImageButton"));
        discardImageButton->setGeometry(QRect(380, 600, 89, 25));
        imageProgressBar = new QProgressBar(Intrinsic);
        imageProgressBar->setObjectName(QString::fromUtf8("imageProgressBar"));
        imageProgressBar->setGeometry(QRect(480, 80, 118, 23));
        imageProgressBar->setValue(24);
        numPics = new QLabel(Intrinsic);
        numPics->setObjectName(QString::fromUtf8("numPics"));
        numPics->setGeometry(QRect(880, 30, 67, 17));
        cancelCalibrationButton = new QPushButton(Intrinsic);
        cancelCalibrationButton->setObjectName(QString::fromUtf8("cancelCalibrationButton"));
        cancelCalibrationButton->setGeometry(QRect(730, 80, 151, 25));
        cameraChosen = new QLabel(Intrinsic);
        cameraChosen->setObjectName(QString::fromUtf8("cameraChosen"));
        cameraChosen->setGeometry(QRect(230, 30, 381, 20));
        infoCalibration = new QTextBrowser(Intrinsic);
        infoCalibration->setObjectName(QString::fromUtf8("infoCalibration"));
        infoCalibration->setGeometry(QRect(260, 290, 256, 61));

        retranslateUi(Intrinsic);

        QMetaObject::connectSlotsByName(Intrinsic);
    } // setupUi

    void retranslateUi(QDialog *Intrinsic)
    {
        Intrinsic->setWindowTitle(QApplication::translate("Intrinsic", "Intrinsic calibration", nullptr));
        labelSelectCam->setText(QApplication::translate("Intrinsic", "Select the camera", nullptr));
        labelNumberPhoto->setText(QApplication::translate("Intrinsic", "Number of Photos", nullptr));
        startCalibrButton->setText(QApplication::translate("Intrinsic", "Start", nullptr));
        closeButton->setText(QApplication::translate("Intrinsic", "Close", nullptr));
        pictureButton->setText(QApplication::translate("Intrinsic", "Take picture", nullptr));
        labelCalibrationError->setText(QApplication::translate("Intrinsic", "Calibration error:", nullptr));
        repeatButton->setText(QApplication::translate("Intrinsic", "Repeat", nullptr));
        saveButton->setText(QApplication::translate("Intrinsic", "Save", nullptr));
        loadButton->setText(QApplication::translate("Intrinsic", "Load", nullptr));
        label_CameraFeed->setText(QString());
        saveImage->setText(QApplication::translate("Intrinsic", "Save image ?", nullptr));
        saveImageButton->setText(QApplication::translate("Intrinsic", "Save", nullptr));
        discardImageButton->setText(QApplication::translate("Intrinsic", "Discard", nullptr));
        numPics->setText(QString());
        cancelCalibrationButton->setText(QApplication::translate("Intrinsic", "Cancel", nullptr));
        cameraChosen->setText(QString());
        infoCalibration->setHtml(QApplication::translate("Intrinsic", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">All images have been colected!</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Calibrating now, please wait !</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Intrinsic: public Ui_Intrinsic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTRINSIC_H
