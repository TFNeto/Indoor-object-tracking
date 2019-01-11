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
    explicit extrinsic_compute();
    void load_image_points(int num_imgs, string leftimg_dir, string rightimg_dir, string leftimg_filename, string rightimg_filename);
    int run_extrinsic(int num_imgs, string leftcalib_file, string rightcalib_file, string leftimg_dir, string rightimg_dir,string leftimg_filename, string rightimg_filename, string out_file);

private:
    vector<vector<Point3f>> object_points;
    vector<vector<Point2f>> imagePoints1, imagePoints2;
    vector<Point2f> corners1, corners2;
    vector<vector<Point2f>> left_img_points;
    vector<vector<Point2f>> right_img_points;
    Mat img1, img2, gray1, gray2;

};

#endif // EXTRINSIC_COMPUTE_H
