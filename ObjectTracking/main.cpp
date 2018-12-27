#include "mainwindow.h"
#include <QApplication>
Q_DECLARE_METATYPE(Camera);

int main(int argc, char *argv[])
{
    qRegisterMetaTypeStreamOperators<Camera>("Camera");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
