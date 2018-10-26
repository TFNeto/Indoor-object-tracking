#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    VideoCapture cap(0);
    if (!cap.isOpened())  // if not success, exit program
        cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;

    namedWindow("Webcam Feed",CV_WINDOW_AUTOSIZE); //create a window to display our webcam feed

    int stop=0;
    while (0==stop) {

        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from camera feed

        if (!bSuccess) //test if frame successfully read
        {
            cout << "ERROR READING FRAME FROM CAMERA FEED" << endl;
            break;
        }


        imshow("Webcam Feed", frame); //show the frame in "MyVideo" window

        //EVENT HANDLING
        switch(waitKey(10)){ //listen for 10ms for a key to be pressed

        case 27:
            //'esc' has been pressed (ASCII value for 'esc' is 27)
            //exit program.
            stop=1;
            break;
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
