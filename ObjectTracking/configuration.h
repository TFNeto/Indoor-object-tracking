#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "camera.h"
#include <QDialog>
#include <vector>
#include <string>

using namespace std;

namespace Ui {
class Configuration;
}

class Configuration : public QDialog
{
    Q_OBJECT
public:
    explicit Configuration(QWidget *parent = nullptr);
    ~Configuration();
    void updateTable(vector<Camera>);
private slots:
    void on_close_pushButton_clicked();
    void on_addCam_push_clicked();
    void on_tableWidget_cellClicked(int row, int column);
    void on_saveCon_push_clicked();
    void on_loadCon_push_clicked();

private:
    Ui::Configuration *ui;
};

#endif // CONFIGURATION_H
