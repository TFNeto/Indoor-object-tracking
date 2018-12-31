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
    void on_closeButton_clicked();
    void on_cameraDropdown_currentIndexChanged(int index);
    void on_calibrateButton_clicked();
    void on_comboBox_2_currentIndexChanged();

private:
    Ui::extrinsic *ui;
};

#endif // EXTRINSIC_H
