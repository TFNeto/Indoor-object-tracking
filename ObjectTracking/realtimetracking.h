#ifndef REALTIMETRACKING_H
#define REALTIMETRACKING_H

#include <QDialog>

namespace Ui {
    class RealTimeTracking;
}

class RealTimeTracking : public QDialog
{
    Q_OBJECT

public:
    explicit RealTimeTracking(QWidget *parent = 0);
    ~RealTimeTracking();

private:
    Ui::RealTimeTracking *ui;
};

#endif // REALTIMETRACKING_H
