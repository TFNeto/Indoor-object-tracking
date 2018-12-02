#include <iostream>
#include <unistd.h>
#include "serial.h"

using namespace std;

int main(int argc, char *argv[])
{
  try
  {
    cout << "Starting..."  << endl;

    // Create new serial object
    SimpleSerial serial("/dev/ttyS6", 115200);
        // SimpleSerial serial("COM5", 9600);

    serial.writeString("n2");
    cout << "Sent c1" << endl;

    // Read back
    // cout << "Received " << serial.readLine() << endl;
    // cout << "Readback complete" << endl;
  }
  catch (boost::system::system_error &e)
  {
    cout << "Error: " << e.what() << endl;
    return 1;
  }
}

