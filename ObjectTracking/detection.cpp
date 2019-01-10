#include "detection.hpp"

#define standalone 0

std::vector<cv::Rect2d> object_shape_detection (cv::Mat &im) //the image is the input
{
    cv::Mat im2=im;
    cvtColor(im2,im2,cv::COLOR_BGR2GRAY);

    std::vector<cv::Vec3f> circles;
    HoughCircles( im2, circles, CV_HOUGH_GRADIENT, 2, im.rows/8, 200, 100, 1, 200 );


    std::vector<cv::Rect2d> markers; //used to pass to next step
    cv::Rect2d aux;

    /// Store the circles detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
#if showCircles
        // circle center
        circle( im, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( im, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
#endif
        aux.x = center.x-radius;
        aux.y = center.y-radius;
        aux.width = radius*2;
        aux.height=aux.width;
        markers.push_back(aux);
    }

    return markers;
}


cv::Mat object_color_detection (cv::Mat im) //the image is the input
{

   cv::Mat HSV_image;

    cvtColor(im,HSV_image,cv::COLOR_BGR2HSV);
    medianBlur(HSV_image, HSV_image, 5); //makes everything more uniform, less false positives

    cv::Mat dilatedImage, erodedImage;
    cv::Mat erodeElement = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5));
    cv::Mat dilateElement = getStructuringElement( cv::MORPH_ELLIPSE, cv::Size(8,8));

    erode(HSV_image, erodedImage, erodeElement);
    dilate(HSV_image, dilatedImage, dilateElement);
    cv::Mat img = dilatedImage-erodedImage; //gradient makes balls easier to spot

    dilateElement = getStructuringElement( cv::MORPH_ELLIPSE, cv::Size(1,1));
    erode(img, img, erodeElement); //erode further
    dilate(img, img, dilateElement); //fill tiny gaps

#if showCircles
    cv::imshow("postMorphOps", img);
    cv::waitKey(0);
#endif

    return img;//colored
}


#if standalone
int main()
{
    
    std::string imgPath1 = "/home/user/Desktop/real1.png"; //change path here

    cv::Mat im = imread(imgPath1);
    cv::Mat res1;

    res1 = object_color_detection(im);
    std::vector<cv::Rect2d> nextStageVar = object_shape_detection(res1);
#if showCircles
    cv::imshow("final", res1);
    cv::waitKey(0);
#endif
    
   return 0;
}
#endif