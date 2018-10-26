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
}
