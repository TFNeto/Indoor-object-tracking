#ifndef INTRINSIC_H
#define INTRINSIC_H

#include <QDialog>

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

private slots:
    void on_startCalibrButton_clicked();
    void on_pictureButton_clicked();
    void on_closeButton_clicked();
    void on_repeatButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();

private:
    Ui::Intrinsic *ui;
};

#endif // INTRINSIC_H
