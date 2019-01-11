#include "realtimetracking.h"
#include "ui_realtimetracking.h"
#include <thread>
#include "camerafly.h"
#include "CamTracking.hpp"
#include <string>

#include "global.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define THREADS_ENABLE 0

//contains data for the last result of each tracking operation.
//if you want to add this to the class private members, you'll have to add trackingthread as a friend
static std::vector<std::vector<cv::Rect2d>> g_2dData;

cv::Mat K, D, P1, P2;

/*
Maybe the code for the stop recording button:
    for(size_t i=0; i < tvec.size(); i++)
    {
        delete tvec[i]; //threads were allocated dinamically so just dealloc and hope it doesn't cause the pc to explode?
    }
*/

QVector3D CvtoQtCoordinates(cv::Point3d rect){
    QVector3D out;
    out.setX((float)rect.x);
    out.setY((float)rect.y);
    out.setZ((float)rect.z);
    return out;
}

QVector<QVector3D> cvtCoordinates(std::vector<cv::Point3d> vec){
    QVector<QVector3D> out;
    for(size_t i = 0; i<vec.size();i++)
    {
        out.push_back(CvtoQtCoordinates(vec[i]));
    }
    return out;
}

void trackingthread(int id)
{
    std::cout << "Entering thread " << id << std::endl;
    cv::Mat undistortedImg;
    // Get image from camera
    FlyCapture2::Image Image = takeSinglePictureFromSingleCamera(id);
    // Convert image to OpenCV Mat

    unsigned int rowBytes = static_cast<double>(Image.GetReceivedDataSize())/static_cast<double>(Image.GetRows());
    cv::Mat imgcv = cv::Mat(Image.GetRows(), Image.GetCols(), CV_8UC3, Image.GetData(),rowBytes);
    // Get intrinsic calib values


    //cout << "K size: " << K.size() << endl;
    //cout << "D size: " << D.size() << endl;
    //cv::Mat cameraMatrix = listOfCameras[id].getCameraMatrix();
    //cv::Mat distCoeffs = listOfCameras[id].getDistCoeffs();
    // Undistort image
    cv::undistort(imgcv, undistortedImg, K, D);



    // Start tracking
    std::string trackerType = "CSRT";
    CamTracking ct(id, trackerType, undistortedImg);

    while(true)
    {
        cv::Mat undistortedImg;
        // Get image from camera
        FlyCapture2::Image Image = takeSinglePictureFromSingleCamera(id);
        // Convert image to OpenCV Mat
        unsigned int rowBytes = static_cast<double>(Image.GetReceivedDataSize())/static_cast<double>(Image.GetRows());
        cv::Mat imgcv = cv::Mat(Image.GetRows(), Image.GetCols(), CV_8UC3, Image.GetData(),rowBytes);
        // Undistort image
        cv::undistort(imgcv, undistortedImg, K, D);

        g_2dData[id] = ct.track(undistortedImg);

        for(size_t i=0;i<g_2dData[id].size();i++){
            std::cout << "Thread " << id << ": Object: " << i << ": " << g_2dData[id][i].x << " " << g_2dData[id][i].y << std::endl;
            cv::rectangle(undistortedImg,g_2dData[id][i],cv::Scalar(0,255,255));
        }

#if !THREADS_ENABLE
        imshow("test",undistortedImg);
        cv::waitKey(1);
#endif

    }
}

void updatethread(RealTimeTracking* rtt){

    bool toUpdate=false;
    while(!toUpdate){
        toUpdate=true;
        for(size_t i=0;i<g_2dData.size();i++)
            toUpdate = toUpdate && !g_2dData[i].empty();
    }

    std::vector<cv::Point2d> cog;
    for(size_t thread=0;thread<g_2dData.size();thread++){
        cog.push_back(cv::Point2d(0,0));
        for(size_t obj = 0; obj<g_2dData[thread].size(); obj++){
            cog[thread].x += g_2dData[thread][obj].x/g_2dData[thread].size();
            cog[thread].y += g_2dData[thread][obj].y/g_2dData[thread].size();
        }
        cout << "Update Thread Average " << thread << " - " << cog[thread].x << " " << cog[thread].y << std::endl;
    }

    std::vector<cv::Point3d> data3d; //output triangulation to here

    cv::Mat m1(2,1,CV_64FC2);
    cv::Mat m2(2,1,CV_64FC2);

    m1.at<double>(0,0)=cog[0].x;
    m1.at<double>(1,0)=cog[0].y;

    m2.at<double>(0,0)=cog[1].x;
    m2.at<double>(1,0)=cog[1].y;

    std::vector<cv::Point2d> d1;
    std::vector<cv::Point2d> d2;
    d1.push_back(cog[0]);
    d2.push_back(cog[1]);



    cv::triangulatePoints(P1,P2,m1,m2,data3d);

    //----------triangulate here---------
    //you can convert Rect2D to Point2D with Point2D(Rect2D.x,Rect2D.y)

    for(size_t i=0;i<g_2dData.size();i++){
        g_2dData[i] = std::vector<cv::Rect2d>(); //empty the vectors
    }

    //data3d.push_back() // add cameras position or extreme points to keep the graphic always on same dimensions
    rtt->modifier->setData(cvtCoordinates(data3d));
}

RealTimeTracking::RealTimeTracking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RealTimeTracking)
{
    graph = new QtDataVisualization::Q3DScatter;
    container = QWidget::createWindowContainer(graph);
    modifier = new ScatterDataModifier(graph);
    modifier->addData();
    ui->setupUi(this);
    ui->gridLayout->addWidget(container);
    ui->stopRec_pushButton->setVisible(false);
}

RealTimeTracking::~RealTimeTracking()
{
    delete ui;
}

void RealTimeTracking::on_RandomizeButton_clicked()
{
    modifier->addData();
}

void RealTimeTracking::on_stopRec_pushButton_clicked()
{
    ui->stopRec_pushButton->setVisible(false);
    ui->startRec_pushButton->setVisible(true);

    for(size_t i = 0; i < tvec.size(); i++)
    {
        tvec[i]->detach();
    }
}

void RealTimeTracking::on_startRec_pushButton_clicked()
{
    ui->stopRec_pushButton->setVisible(true);
    ui->startRec_pushButton->setVisible(false);

    cv::FileStorage fsl("a", cv::FileStorage::READ);
    fsl["K"] >> K;
    fsl["D"] >> D;
    fsl["P1"] >> P1;
    fsl["P2"] >> P2;

    connectAllCameras();
    g_2dData.push_back(std::vector<cv::Rect2d>());
    trackingthread(0);
#if THREADS_ENABLE
        for(int i = 0; i < listOfCameras.size(); i++)
        {
            g_2dData.push_back(std::vector<cv::Rect2d>()); //adds empty vector to avoid segfault
            std::thread *t = new std::thread(trackingthread, i);
            tvec.push_back(t);
        }
        tvec.push_back(new std::thread(updatethread,this));
        for(size_t i=0; i < tvec.size(); i++)
        {
            tvec[i]->detach();
        }

#endif
}
