#include <sstream>
#include <string>
#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "marker.h"
#include <vector>

using namespace cv;
using namespace std;

//initial min and max HSV filter values.
//these will be changed using trackbars
static int H_MIN = 0;
static int H_MAX = 256;
static int S_MIN = 0;
static int S_MAX = 256;
static int V_MIN = 0;
static int V_MAX = 256;
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 40*40;
const int MAX_OBJECT_AREA = static_cast<int>(FRAME_HEIGHT*FRAME_WIDTH/1.5);
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";
void on_trackbar( int, void* )
{//This function gets called whenever a
    // trackbar position is changed
}
string intToString(int number){


    std::stringstream ss;
    ss << number;
    return ss.str();
}
void createTrackbars(){
    //create window for trackbars

    namedWindow(trackbarWindowName,0);
    //create memory to store trackbar name on window
    char TrackbarName[50];
    sprintf( TrackbarName, "H_MIN", H_MIN);
    sprintf( TrackbarName, "H_MAX", H_MAX);
    sprintf( TrackbarName, "S_MIN", S_MIN);
    sprintf( TrackbarName, "S_MAX", S_MAX);
    sprintf( TrackbarName, "V_MIN", V_MIN);
    sprintf( TrackbarName, "V_MAX", V_MAX);
    //create trackbars and insert them into window
    //3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
    //the max value the trackbar can move (eg. H_HIGH),
    //and the function that is called whenever the trackbar is moved(eg. on_trackbar)
    //                                  ---->    ---->     ---->
    createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar );

    //mark has hue 12-40 (apox.), set position of trackbar
    setTrackbarPos("H_MIN", trackbarWindowName, 17); //12*360/255
    setTrackbarPos("H_MAX", trackbarWindowName, 57); //40*360/255
}
void drawObject(vector<marker> markers,Mat &frame){
    unsigned int i=0;
    for(i=0;i <markers.size();i++)
    {
        int x=markers.at(i).get_xPOS();
        int y=markers.at(i).get_yPOS();
        cv::circle(frame,cv::Point(x,y),10,cv::Scalar(0,0,255));
        cv::putText(frame,intToString(x)+ " , " + intToString(y),cv::Point(x,y+20),1,1,Scalar(0,255,0));
    }
}
void morphOps(Mat &thresh){

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle

    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);


    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);

}
void trackFilteredObject(Mat threshold,Mat HSV, Mat &cameraFeed){

    vector<marker> markers;

    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){

            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.

                if(area>MIN_OBJECT_AREA){
                    marker mark;
                    mark.set_xPOS(moment.m10/area);
                    mark.set_yPOS(moment.m01/area);

                    markers.push_back(mark);

                    objectFound = true;

                }else objectFound = false;


            }
            //let user know you found an object
            if(objectFound ==true){
                //draw object location on screen
                drawObject(markers, cameraFeed);}

        }else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
    }
}

int main()
{
    bool usingVideo = true;

    bool calibrationMode = false; //if we would like to calibrate our filter values, set to true.

    //Matrix to store each frame of the webcam feed

    if(usingVideo)
    {
        Mat cameraFeed;
        Mat threshold;
        Mat HSV;

        if(calibrationMode){
            //create slider bars for HSV filtering
            createTrackbars();
        }
        //video capture object to acquire webcam feed
        VideoCapture capture(0);
        //open capture object at location zero (default location for webcam)
        if(!capture.isOpened())
        {
            cout << "Problem opening camera main.cpp:166";
            return 0;
        }
        //set height and width of capture frame
        capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);


        //start an infinite loop where webcam feed is copied to cameraFeed matrix
        //all of our operations will be performed within this loop
        int stop=0;
        while (0==stop){
            //store image to matrix
            if(!capture.read(cameraFeed))
            {
                cout << "couldnt read feed";
                continue;
            }
            //convert frame from BGR to HSV colorspace
            cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);

            if(calibrationMode==true){
                //if in calibration mode, we track objects based on the HSV slider values.
                cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
                inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
                morphOps(threshold);
                imshow(windowName2,threshold);
                trackFilteredObject(threshold,HSV,cameraFeed);
            }

            //show frames
            //imshow(windowName2,threshold);

            imshow(windowName,cameraFeed);
            //imshow(windowName1,HSV);

            //image will not appear without this waitKey() command

            switch(waitKey(0))//listen for 10ms for a key to be pressed and so that screen can refresh
            {
            case 27:
                //'esc' has been pressed (ASCII value for 'esc' is 27)
                //exit program.
                cout << "esc has been pressed\n";
                stop=1;
                break;

            }
        }
    }







    else //not using video
    {
        Mat inputImage = cv::imread("/home/bruno/Desktop/fruits.jpg");
        Mat HSV;
        Mat threshold;

        if(!inputImage.empty())
        {
            imshow("Display Image", inputImage);
        }
        else
        {
            cout << "\nNo image found\n";
            return 0;
        }

        //waitKey(0);

        cvtColor(inputImage,HSV,COLOR_BGR2HSV);

        if(calibrationMode==true){
            //if in calibration mode, we track objects based on the HSV slider values.
            cvtColor(inputImage,HSV,COLOR_BGR2HSV);
            inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
            morphOps(threshold);
            imshow(windowName2,threshold);
            trackFilteredObject(threshold,HSV,inputImage);
        }
        waitKey(0);
    }

    return 0;
}
