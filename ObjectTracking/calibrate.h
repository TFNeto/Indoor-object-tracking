#ifndef CALIBRATE_H
#define CALIBRATE_H

#include <vector>
#include <QDialog>
#include <string>
#include "camera.h"
#include "intrinsic_compute.h"

using namespace std;

namespace Ui {
class Calibrate;
}

class Calibrate : public QDialog
{
    Q_OBJECT

public:
    explicit Calibrate(QWidget *parent = nullptr);
    ~Calibrate();
    void setCameraInfo();
private slots:
    void on_close_button_clicked();
    void on_intrinsicButton_clicked();
    void on_extrinsicButton_clicked();
private:
    Ui::Calibrate *ui;

};

#endif // CALIBRATE_H
