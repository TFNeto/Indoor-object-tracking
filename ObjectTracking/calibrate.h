#ifndef CALIBRATE_H
#define CALIBRATE_H
#include <vector>
#include <QDialog>
#include <string>
#include "camera.h"

using namespace std;

namespace Ui {
    class Calibrate;
}

class Calibrate : public QDialog
{
    Q_OBJECT

public:
    explicit Calibrate(QWidget *parent = 0);
    ~Calibrate();
    void  setCameraInfo(vector<Camera> listOfCameras);
private slots:
    void on_close_button_clicked();

    void on_pushButton_clicked();

private:
    Ui::Calibrate *ui;
};

#endif // CALIBRATE_H
