#include "intrinsic_compute.h"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
// #include "popt_pp.h"
#include <sys/stat.h>

using namespace std;
using namespace cv;

vector< vector< Point3f > > object_points;
vector< vector< Point2f > > image_points;
vector< Point2f > corners;
vector< vector< Point2f > > left_img_points;

Mat img, gray;
Size im_size;

intrinsic_compute::intrinsic_compute()
{
    //some of these could be fixed
      int board_width, board_height;
      int num_imgs;
      float square_size;
      char* imgs_directory;
      char* imgs_filename;
      char* out_file;
      char* extension;



}
