#include "mainwindow.h"
#include <QApplication>
//#include <opencv/highgui.h>
#include <opencv/cv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

string intToString(int number){


    std::stringstream ss;
    ss << number;
    return ss.str();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    VideoCapture cap(0);
    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;
        return -1;
    }

    namedWindow("Webcam Feed",CV_WINDOW_AUTOSIZE); //create a window to display our webcam feed
    while (1) {

        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from camera feed

        if (!bSuccess) //test if frame successfully read
        {
            cout << "ERROR READING FRAME FROM CAMERA FEED" << endl;
            break;
        }


        imshow("Webcam Feed", frame); //show the frame in "MyVideo" window

        //listen for 10ms for a key to be pressed
        switch(waitKey(10)){

        case 27:
            //'esc' has been pressed (ASCII value for 'esc' is 27)
            //exit program.
            return 0;

        }


    }

    return a.exec();
}
