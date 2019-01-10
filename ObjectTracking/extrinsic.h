#ifndef EXTRINSIC_H
#define EXTRINSIC_H

#include <QDialog>
#include "FlyCapture2.h"

namespace Ui {
class extrinsic;
}

class extrinsic : public QDialog
{
    Q_OBJECT

public:
    explicit extrinsic(QWidget *parent = nullptr);
    ~extrinsic();
    void calibrateCameraPair();
    int counterEx = 0;
    int numPhotoEx = 0;
    bool isCalibratingExtrinsic = false;
    bool saveImageFlagExtrinsic = false;
    bool discardImageFlagExtrinsic = false;
    bool liveFlagExtrinsic = true;
    FlyCapture2::Image convertedImageEX;
    FlyCapture2::Image convertedImageEX2;

private slots:
    void on_takePictureButton_clicked();
    void on_savePictureButton_clicked();
    void on_discardPictureButton_clicked();
    void on_closeButton_clicked();
    void on_calibrateButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::extrinsic *ui;
};

#endif // EXTRINSIC_H
