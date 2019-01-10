/********************************************************************************
** Form generated from reading UI file 'extrinsic.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRINSIC_H
#define UI_EXTRINSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_extrinsic
{
public:
    QSpinBox *numPicsDropdown;
    QComboBox *comboBox;
    QLabel *selectPair;
    QLabel *photoCount;
    QComboBox *comboBox_2;
    QPushButton *calibrateButton;
    QLabel *calibResult;
    QLabel *calibResultText;
    QPushButton *closeButton;
    QPushButton *loadButton;
    QLabel *errorText;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QLabel *camera1Feed;
    QLabel *camera2Feed;
    QLabel *numPicsText;
    QLabel *camera1IP;
    QLabel *camera2IP;
    QPushButton *takePictureButton;
    QPushButton *savePictureButton;
    QPushButton *discardPictureButton;

    void setupUi(QDialog *extrinsic)
    {
        if (extrinsic->objectName().isEmpty())
            extrinsic->setObjectName(QString::fromUtf8("extrinsic"));
        extrinsic->resize(1108, 557);
        numPicsDropdown = new QSpinBox(extrinsic);
        numPicsDropdown->setObjectName(QString::fromUtf8("numPicsDropdown"));
        numPicsDropdown->setGeometry(QRect(950, 30, 48, 26));
        numPicsDropdown->setMinimum(1);
        numPicsDropdown->setMaximum(100);
        comboBox = new QComboBox(extrinsic);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(230, 30, 181, 25));
        selectPair = new QLabel(extrinsic);
        selectPair->setObjectName(QString::fromUtf8("selectPair"));
        selectPair->setGeometry(QRect(20, 30, 181, 21));
        QFont font;
        font.setPointSize(14);
        selectPair->setFont(font);
        photoCount = new QLabel(extrinsic);
        photoCount->setObjectName(QString::fromUtf8("photoCount"));
        photoCount->setGeometry(QRect(740, 30, 141, 17));
        photoCount->setFont(font);
        comboBox_2 = new QComboBox(extrinsic);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(440, 30, 181, 25));
        calibrateButton = new QPushButton(extrinsic);
        calibrateButton->setObjectName(QString::fromUtf8("calibrateButton"));
        calibrateButton->setGeometry(QRect(780, 80, 131, 25));
        calibResult = new QLabel(extrinsic);
        calibResult->setObjectName(QString::fromUtf8("calibResult"));
        calibResult->setGeometry(QRect(60, 510, 141, 17));
        calibResultText = new QLabel(extrinsic);
        calibResultText->setObjectName(QString::fromUtf8("calibResultText"));
        calibResultText->setGeometry(QRect(250, 510, 131, 17));
        closeButton = new QPushButton(extrinsic);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(990, 500, 89, 25));
        loadButton = new QPushButton(extrinsic);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(990, 190, 89, 25));
        errorText = new QLabel(extrinsic);
        errorText->setObjectName(QString::fromUtf8("errorText"));
        errorText->setGeometry(QRect(450, 260, 181, 41));
        saveButton = new QPushButton(extrinsic);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(990, 230, 89, 25));
        cancelButton = new QPushButton(extrinsic);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(990, 80, 89, 25));
        camera1Feed = new QLabel(extrinsic);
        camera1Feed->setObjectName(QString::fromUtf8("camera1Feed"));
        camera1Feed->setGeometry(QRect(60, 160, 441, 294));
        camera2Feed = new QLabel(extrinsic);
        camera2Feed->setObjectName(QString::fromUtf8("camera2Feed"));
        camera2Feed->setGeometry(QRect(540, 160, 441, 294));
        numPicsText = new QLabel(extrinsic);
        numPicsText->setObjectName(QString::fromUtf8("numPicsText"));
        numPicsText->setGeometry(QRect(940, 30, 71, 21));
        camera1IP = new QLabel(extrinsic);
        camera1IP->setObjectName(QString::fromUtf8("camera1IP"));
        camera1IP->setGeometry(QRect(230, 30, 171, 21));
        camera2IP = new QLabel(extrinsic);
        camera2IP->setObjectName(QString::fromUtf8("camera2IP"));
        camera2IP->setGeometry(QRect(440, 30, 171, 21));
        takePictureButton = new QPushButton(extrinsic);
        takePictureButton->setObjectName(QString::fromUtf8("takePictureButton"));
        takePictureButton->setGeometry(QRect(450, 490, 131, 25));
        savePictureButton = new QPushButton(extrinsic);
        savePictureButton->setObjectName(QString::fromUtf8("savePictureButton"));
        savePictureButton->setGeometry(QRect(410, 490, 89, 25));
        discardPictureButton = new QPushButton(extrinsic);
        discardPictureButton->setObjectName(QString::fromUtf8("discardPictureButton"));
        discardPictureButton->setGeometry(QRect(520, 490, 89, 25));
        camera1Feed->raise();
        numPicsDropdown->raise();
        comboBox->raise();
        selectPair->raise();
        photoCount->raise();
        comboBox_2->raise();
        calibrateButton->raise();
        calibResult->raise();
        calibResultText->raise();
        closeButton->raise();
        loadButton->raise();
        errorText->raise();
        saveButton->raise();
        cancelButton->raise();
        camera2Feed->raise();
        numPicsText->raise();
        camera1IP->raise();
        camera2IP->raise();
        takePictureButton->raise();
        savePictureButton->raise();
        discardPictureButton->raise();

        retranslateUi(extrinsic);

        QMetaObject::connectSlotsByName(extrinsic);
    } // setupUi

    void retranslateUi(QDialog *extrinsic)
    {
        extrinsic->setWindowTitle(QApplication::translate("extrinsic", "Extrinsic calibration", nullptr));
        selectPair->setText(QApplication::translate("extrinsic", "Select camera pair", nullptr));
        photoCount->setText(QApplication::translate("extrinsic", "Photo count", nullptr));
        calibrateButton->setText(QApplication::translate("extrinsic", "Calibrate", nullptr));
        calibResult->setText(QApplication::translate("extrinsic", "Calibration result:", nullptr));
        calibResultText->setText(QString());
        closeButton->setText(QApplication::translate("extrinsic", "Close", nullptr));
        loadButton->setText(QApplication::translate("extrinsic", "Load", nullptr));
        errorText->setText(QString());
        saveButton->setText(QApplication::translate("extrinsic", "Save", nullptr));
        cancelButton->setText(QApplication::translate("extrinsic", "Cancel", nullptr));
        camera1Feed->setText(QString());
        camera2Feed->setText(QString());
        numPicsText->setText(QString());
        camera1IP->setText(QString());
        camera2IP->setText(QString());
        takePictureButton->setText(QApplication::translate("extrinsic", "Take Picture", nullptr));
        savePictureButton->setText(QApplication::translate("extrinsic", "Save", nullptr));
        discardPictureButton->setText(QApplication::translate("extrinsic", "Discard", nullptr));
    } // retranslateUi

};

namespace Ui {
    class extrinsic: public Ui_extrinsic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRINSIC_H
