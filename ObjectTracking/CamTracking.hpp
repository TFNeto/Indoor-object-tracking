#ifndef __CAMTRACKING_HPP__
#define __CAMTRACKING_HPP__

#include <vector>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

#define AUTODETECT

class CamTracking{
public:
    CamTracking(int id, std::string &trackerType, cv::Mat firstFrame);
    ~CamTracking(){}
    std::vector<cv::Rect2d> track(cv::Mat frame);
private:
    cv::Ptr<cv::Tracker> createTracker(std::string trackerType);
    std::vector<cv::Rect> getObjects(cv::Mat frame);
    
    cv::Ptr<cv::MultiTracker> multiTracker;
    std::string trackerType;
    int id;
};

#endif
