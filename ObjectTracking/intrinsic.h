#ifndef INTRINSIC_H
#define INTRINSIC_H

#include <QDialog>
#include <string>

#include "FlyCapture2.h"

namespace Ui {
class Intrinsic;
}

class Intrinsic : public QDialog
{
    Q_OBJECT

public:
    explicit Intrinsic(QWidget *parent = nullptr);
    ~Intrinsic();
    void calibrateCamera();
    int counter = 0;
    int numPhoto = 0;
    std::string currentCamera;
    std::string tempFilename;
    // Save state of calibration process
    // Enables live stream, if true
    bool isCalibrating = false;
    bool saveImageFlag = false;
    bool discardImageFlag = false;
    bool liveFlag = true;
    FlyCapture2::Image convertedImage;

private slots:
    void on_startCalibrButton_clicked();
    void on_pictureButton_clicked();
    void on_closeButton_clicked();
    void on_repeatButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void on_saveImageButton_clicked();
    void on_discardImageButton_clicked();
    void on_cancelCalibrationButton_clicked();

private:
    Ui::Intrinsic *ui;
};

#endif // INTRINSIC_H
