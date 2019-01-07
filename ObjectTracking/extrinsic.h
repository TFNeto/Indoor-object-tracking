#ifndef EXTRINSIC_H
#define EXTRINSIC_H

#include <QDialog>

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
