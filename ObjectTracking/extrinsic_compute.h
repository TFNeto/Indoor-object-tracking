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

#ifndef EXTRINSIC_COMPUTE_H
#define EXTRINSIC_COMPUTE_H


class extrinsic_compute
{
public:
    extrinsic_compute();
    void load_image_points(int board_width, int board_height, int num_imgs, float square_size,
                          char* leftimg_dir, char* rightimg_dir, char* leftimg_filename, char* rightimg_filename);
    void run_extrinsic(int num_imgs , char* leftcalib_file, char* rightcalib_file, char* leftimg_dir, char* rightimg_dir,
                       char* leftimg_filename, char* rightimg_filename, char* out_file);
private:
    vector< vector< Point3f > > object_points;
    vector< vector< Point2f > > imagePoints1, imagePoints2;
    vector< Point2f > corners1, corners2;
    vector< vector< Point2f > > left_img_points;
    vector<vector<Point2f> > right_img_points;

    Mat img1;
    Mat img2;
    Mat gray1;
    Mat gray2;
};

#endif // EXTRINSIC_COMPUTE_H
