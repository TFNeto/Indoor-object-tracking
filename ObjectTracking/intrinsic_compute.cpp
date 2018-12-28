#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>

#include "intrinsic_compute.h"

using namespace std;
using namespace cv;

// function definition
intrinsic_compute::intrinsic_compute()
{

}

bool intrinsic_compute::doesExist(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

float intrinsic_compute::setupCalibration(int board_width, int board_height, int num_imgs, float square_size, char* imgs_directory, char* imgs_filename, char* extension)
{
  Size board_size = Size(board_width, board_height);
  // int board_n = board_width * board_height;

  // compute stuff for every single image in the folder
  for (int k = 1; k <= num_imgs; k++) {
    bool found = false;
    char img_file[100];
    sprintf(img_file, "%s%s%d.%s", imgs_directory, imgs_filename, k, extension);

    if(!doesExist(img_file)) //skips current iteration if img does not exist?
      continue;

    img = imread(img_file, CV_LOAD_IMAGE_COLOR); //read current image
    cvtColor(img, gray, CV_BGR2GRAY);

    //find chessboard corners
    found = findChessboardCorners(img, board_size, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) //optimize this
    {
      cornerSubPix(gray, corners, cv::Size(5, 5), cv::Size(-1, -1),
                   TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
      drawChessboardCorners(gray, board_size, corners, found);

        vector< Point3f > obj;
        for (int i = 0; i < board_height; i++)
          for (int j = 0; j < board_width; j++)
            obj.push_back(Point3f(static_cast<float>(j)* square_size, static_cast<float>(i) * square_size, 0));

        image_points.push_back(corners);
        object_points.push_back(obj);
      }
  }
  // TODO @TiagoA: Add return (this function is defined as returning a float)
}

double intrinsic_compute::computeReprojectionErrors(const vector< vector< Point3f > >& objectPoints,
                                 const vector< vector< Point2f > >& imagePoints,
                                 const vector< Mat >& rvecs, const vector< Mat >& tvecs,
                                 const Mat& cameraMatrix , const Mat& distCoeffs)
{
  vector< Point2f > imagePoints2;
  int totalPoints = 0;
  double totalErr = 0, err;
  vector<float> perViewErrors;
  perViewErrors.resize(objectPoints.size());

  for (size_t i = 0; i < objectPoints.size(); ++i)
  {
    projectPoints(Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix,
                  distCoeffs, imagePoints2);
    err = norm(Mat(imagePoints[i]), Mat(imagePoints2), CV_L2);
    int n = static_cast<int>(objectPoints[i].size());
    perViewErrors[i] = static_cast<float>(sqrt(err*err/n));
    totalErr += err*err;
    totalPoints += n;
  }
  return sqrt(totalErr/totalPoints);
}


double intrinsic_compute::run(int num_imgs, char* imgs_directory, char* imgs_filename) //nr of images to read, %foldername%, "left" or "right"
{
        //some of these could be constant
        int board_width = 0, board_height = 0; //checkerboard width heigth
        float square_size = 0.0; //checkerboard square size
        char* out_file = nullptr;
        char* extension = nullptr;
        double err = 0;
        Mat K;
        Mat D;
        vector< Mat > rvecs, tvecs;
        int flag = 0;

        setupCalibration(board_width, board_height, num_imgs, square_size, imgs_directory, imgs_filename, extension);

        flag |= CV_CALIB_FIX_K4;
        flag |= CV_CALIB_FIX_K5;

        calibrateCamera(object_points, image_points, img.size(), K, D, rvecs, tvecs, flag);
        err = computeReprojectionErrors(object_points, image_points, rvecs, tvecs, K, D);

        FileStorage fs(out_file, FileStorage::WRITE);
        fs << "K" << K;
        fs << "D" << D;
        fs << "board_width" << board_width;
        fs << "board_height" << board_height;
        fs << "square_size" << square_size;

        return err;
}
