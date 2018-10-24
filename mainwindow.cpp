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
    cv::Mat inputImage = cv::imread("/home/bruno/Desktop/kittens.jpg");

    if(!inputImage.empty())
        cv::imshow("Display Image", inputImage);
    else
        std::cout << "No image found";
}

MainWindow::~MainWindow()
{
    delete ui;
}
