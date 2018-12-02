#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "configuration.h"
#include "calibrate.h"
#include "realtimetracking.h"
#include "trackinglog.h"
#include "camera.h"
#include <QMainWindow>
#include <string>
#include <vector>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void enablePushButtons();
    void disablePushButtons();
    vector<Camera> loadCameraMock();

private slots:

    void on_configure_pushButton_clicked();

    void on_start_pushButton_clicked();

    void on_calibrate_pushButton_clicked();

    void on_log_pushButton_clicked();

private:
    bool camerasCalibrated ;
    Ui::MainWindow *ui;
    Configuration configWindow;
    Calibrate calibrationWindow;
    RealTimeTracking trackWindow;
    TrackingLog logWindow;
};

#endif // MAINWINDOW_H
