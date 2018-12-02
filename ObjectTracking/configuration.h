#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QDialog>
#include <vector>
#include <string>
#include "camera.h"

using namespace std;

namespace Ui {
    class Configuration;
}

class Configuration : public QDialog
{
    Q_OBJECT
private:
    vector<Camera> listOfCameras;

public:
    explicit Configuration(QWidget *parent = 0);
    ~Configuration();
    vector<Camera> getListOfCameras();

private slots:
    void on_close_pushButton_clicked();
    void on_addCam_push_clicked();
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::Configuration *ui;
};

#endif // CONFIGURATION_H
