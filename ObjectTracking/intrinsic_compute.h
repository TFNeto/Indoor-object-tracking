#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;
using namespace cv;

#ifndef INTRINSIC_COMPUTE_H
#define INTRINSIC_COMPUTE_H


class intrinsic_compute
{
public:
    explicit intrinsic_compute();

    bool doesExist(const std::string& name);
    float setupCalibration(int board_width, int board_height, int num_imgs, float square_size, char* imgs_directory, char* imgs_filename, char* extension);
    double computeReprojectionErrors(const vector< vector< Point3f > >& objectPoints,
                              const vector< vector< Point2f > >& imagePoints,
                              const vector< Mat >& rvecs, const vector< Mat >& tvecs,
                              const Mat& cameraMatrix , const Mat& distCoeffs);
    double run(int num_imgs, char* imgs_directory, char* imgs_filename);
};

#endif // INTRINSIC_COMPUTE_H
