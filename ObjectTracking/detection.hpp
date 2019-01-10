#ifndef __DETECTION_HPP__
#define __DETECTION_HPP__
#define showCircles 0

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <string>

std::vector<cv::Rect2d> object_shape_detection (cv::Mat &im);
cv::Mat object_color_detection (cv::Mat im);

#endif