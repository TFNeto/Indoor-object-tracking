#ifndef TRACKINGLOG_H
#define TRACKINGLOG_H

#include <QDialog>

namespace Ui {
class TrackingLog;
}

class TrackingLog : public QDialog
{
    Q_OBJECT

public:
    explicit TrackingLog(QWidget *parent = nullptr);
    ~TrackingLog();

private slots:
    void on_close_pushButton_clicked();

private:
    Ui::TrackingLog *ui;
};

#endif // TRACKINGLOG_H
