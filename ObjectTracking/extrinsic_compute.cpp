#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <string>

#include "extrinsic_compute.h"

using namespace std;
using namespace cv;


extrinsic_compute::extrinsic_compute()
{

}

void extrinsic_compute::load_image_points (int board_width, int board_height, int num_imgs, float square_size,
                          string leftimg_dir, string rightimg_dir, string leftimg_filename, string rightimg_filename)
{

    Size board_size = Size(board_width, board_height);
     int board_n = board_width * board_height;

     for (int i = 1; i <= num_imgs; i++) {
       char left_img[100], right_img[100];
       sprintf(left_img, "%s/%s%d.jpg", leftimg_dir.c_str(), leftimg_filename.c_str(), i);
       sprintf(right_img, "%s/%s%d.jpg", rightimg_dir.c_str(), rightimg_filename.c_str(), i);

       //test
       /*cout << "left_img: " << left_img << "\n";
       cout << "right_img: " << right_img  << "\n";*/

       img1 = imread(left_img, CV_LOAD_IMAGE_COLOR);
       img2 = imread(right_img, CV_LOAD_IMAGE_COLOR);
       cvtColor(img1, gray1, CV_BGR2GRAY);
       cvtColor(img2, gray2, CV_BGR2GRAY);

       bool found1 = false, found2 = false;

       found1 = cv::findChessboardCorners(img1, board_size, corners1,
     CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
       found2 = cv::findChessboardCorners(img2, board_size, corners2,
     CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);


       if(!found1 || !found2){
         cout << "Chessboard find error!" << endl;
         cout << "leftImg: " << left_img << " and rightImg: " << right_img <<endl;
         continue;
       }

       if (found1)
       {
         cv::cornerSubPix(gray1, corners1, cv::Size(5, 5), cv::Size(-1, -1),
     cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
         cv::drawChessboardCorners(gray1, board_size, corners1, found1);
       }
       if (found2)
       {
         cv::cornerSubPix(gray2, corners2, cv::Size(5, 5), cv::Size(-1, -1),
     cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
         cv::drawChessboardCorners(gray2, board_size, corners2, found2);
       }

       vector< Point3f > obj;
       for (int i = 0; i < board_height; i++)
         for (int j = 0; j < board_width; j++)
           obj.push_back(Point3f(static_cast<float>(j)* square_size, static_cast<float>(i) * square_size, 0));

       if (found1 && found2) {
         cout << i << ". Found corners!" << endl;
         imagePoints1.push_back(corners1);
         imagePoints2.push_back(corners2);
         object_points.push_back(obj);


       }
     }
     for (int i = 0; i < imagePoints1.size(); i++) {
       vector< Point2f > v1, v2;
       for (int j = 0; j < imagePoints1[i].size(); j++) {
         v1.push_back(Point2f(static_cast<float>(imagePoints1[i][j].x), static_cast<float>(imagePoints1[i][j].y)));
         v2.push_back(Point2f(static_cast<float>(imagePoints2[i][j].x), static_cast<float>(imagePoints2[i][j].y)));
       }
       left_img_points.push_back(v1);
       right_img_points.push_back(v2);
     }


}

void extrinsic_compute::run_extrinsic(int num_imgs , string leftcalib_file, string rightcalib_file, string leftimg_dir, string rightimg_dir,
                   string leftimg_filename, string rightimg_filename, string out_file)   //rotine for extrinsic pair calibration
{

      FileStorage fsl(leftcalib_file.c_str(), FileStorage::READ);   //lê os parâmetros obtidos na calibração intrinseca
      FileStorage fsr(rightcalib_file.c_str(), FileStorage::READ);

      load_image_points(fsl["board_width"], fsl["board_height"], num_imgs, fsl["square_size"],
                       leftimg_dir.c_str(), rightimg_dir.c_str(), leftimg_filename.c_str(), rightimg_filename.c_str());

      Mat K1, K2, R, F, E;
      Vec3d T;
      Mat D1, D2;
      fsl["K"] >> K1;
      fsr["K"] >> K2;
      fsl["D"] >> D1;
      fsr["D"] >> D2;
      int flag = 0;
      flag |= CV_CALIB_FIX_INTRINSIC;


      stereoCalibrate(object_points, left_img_points, right_img_points, K1, D1, K2, D2, img1.size(), R, T, E, F);

      cv::FileStorage fs1(out_file.c_str(), cv::FileStorage::WRITE);
      fs1 << "K1" << K1;
      fs1 << "K2" << K2;
      fs1 << "D1" << D1;
      fs1 << "D2" << D2;
      fs1 << "R" << R;
      fs1 << "T" << T;
      fs1 << "E" << E;
      fs1 << "F" << F;


      cv::Mat R1, R2, P1, P2, Q;
      stereoRectify(K1, D1, K2, D2, img1.size(), R, T, R1, R2, P1, P2, Q);

      fs1 << "R1" << R1;
      fs1 << "R2" << R2;
      fs1 << "P1" << P1;
      fs1 << "P2" << P2;
      fs1 << "Q" << Q;

}
