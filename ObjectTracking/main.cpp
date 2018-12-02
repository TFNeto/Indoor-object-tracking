// C++ apis
#include <iostream>
#include <unistd.h>

// Qt related includes
#include "mainwindow.h"
#include <QApplication>

// Serial communication
#include "serial.h"

int main(int argc, char *argv[])
{
    /*
    // Init serial communication
    try
    {
      std::cout << "Starting..."  << std::endl;

      // Create new serial object
      SimpleSerial serial("/dev/ttyS6", 115200);

      serial.startSync(10);
      std::cout << "Sent n10" << std::endl;

      // Read back
      // cout << "Received " << serial.readLine() << endl;
      // cout << "Readback complete" << endl;
    } catch(boost::system::system_error const& e) {
        std::cout << e.what() << ": " << e.code() << " - " << e.code().message() << std::endl;
        return 1;
    }
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
