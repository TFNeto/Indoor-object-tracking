#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <string>

using namespace std;
using namespace cv;

#ifndef INTRINSIC_COMPUTE_H
#define INTRINSIC_COMPUTE_H


class intrinsic_compute
{
public:
    explicit intrinsic_compute();

    bool doesExist(const std::string& name);
    void setupCalibration(int board_width, int board_height, int num_imgs, float square_size, string imgs_directory, string imgs_filename, string extension);
    double computeReprojectionErrors(const vector< vector< Point3f > >& objectPoints,
                              const vector< vector< Point2f > >& imagePoints,
                              const vector< Mat >& rvecs, const vector< Mat >& tvecs,
                              const Mat& cameraMatrix , const Mat& distCoeffs);
    double run(int num_imgs, string imgs_directory, string imgs_filename);

private:
    vector<vector<Point3f>> object_points;
    vector<vector<Point2f>> image_points;
    vector<Point2f> corners;
    vector<vector<Point2f>> left_img_points;
    Mat img, gray;
    Size im_size;
};

#endif // INTRINSIC_COMPUTE_H
