#include "mainwindow.h"
#include "simpleserial.h"
#include <QApplication>
Q_DECLARE_METATYPE(Camera);

int main(int argc, char *argv[])
{
    cout << "Starting..."  << endl;

       // Create new serial object
    SimpleSerial serial("/dev/ttyUSB0", 115200);
    usleep(2000000);

    serial.writeString("n10");
    cout << "Sent n30" << endl;

    qRegisterMetaTypeStreamOperators<Camera>("Camera");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
