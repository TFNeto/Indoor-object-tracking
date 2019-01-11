#include "CamTracking.hpp"
#include "detection.hpp"

std::vector<cv::Rect2d> CamTracking::track(cv::Mat frame){
    multiTracker->update(frame);
    return multiTracker->getObjects();
}

CamTracking::CamTracking(int i, std::string &type, cv::Mat frame){
    id = i;
    trackerType = type;
    std::vector<cv::Rect> bboxes = getObjects(frame);
    multiTracker = cv::MultiTracker::create();
    for(int i=0; i < bboxes.size(); i++){
        multiTracker->add(createTracker(trackerType), frame, cv::Rect2d(bboxes[i])); 
    }
}

cv::Ptr<cv::Tracker> CamTracking::createTracker(std::string trackerType)
{
    cv::Ptr<cv::Tracker> tracker;
    if (trackerType == "BOOSTING")
        tracker = cv::TrackerBoosting::create();
    else if (trackerType == "MIL")
        tracker = cv::TrackerMIL::create();
    else if (trackerType == "KCF")
        tracker = cv::TrackerKCF::create();
    else if (trackerType == "TLD")
        tracker = cv::TrackerTLD::create();
    else if (trackerType == "MEDIANFLOW")
        tracker = cv::TrackerMedianFlow::create();
    else if (trackerType == "GOTURN")
        tracker = cv::TrackerGOTURN::create();
    else if (trackerType == "MOSSE")
        tracker = cv::TrackerMOSSE::create();
    else if (trackerType == "CSRT")
        tracker = cv::TrackerCSRT::create();
    else
        throw("not a valid tracker");


    return tracker;
}

std::vector<cv::Rect> CamTracking::getObjects(cv::Mat frame){

    std::vector<cv::Rect> vec;

#ifdef AUTODETECT
    cv::Mat res1;
    res1 = object_color_detection(frame);
    std::vector<cv::Rect2d> nextStageVar = object_shape_detection(res1);
    for(int i = 0; i < nextStageVar.size(); i++)
    {
        vec.push_back(cv::Rect(nextStageVar[i].x,nextStageVar[i].y,nextStageVar[i].width,nextStageVar[i].height));
    }
#else
    selectROIs("Pick regions",frame,vec,true,false);
    cv::destroyWindow("Pick regions");
#endif
    return vec;
}

void CamTracking::detect(cv::Mat frame){
    std::vector<cv::Rect> bboxes = getObjects(frame);
    multiTracker = cv::MultiTracker::create();
    for(int i=0; i < bboxes.size(); i++){
        multiTracker->add(createTracker(trackerType), frame, cv::Rect2d(bboxes[i]));
    }
}
