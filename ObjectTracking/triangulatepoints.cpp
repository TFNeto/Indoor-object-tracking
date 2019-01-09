#include "triangulatepoints.h"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

Mat TriangulatePoints(string file_directory, string file_name, Mat cam0pnts, Mat cam1pnts)

{
    // obter parâmetros Intrinsecos e extrinsecos
    string file= "../" + file_directory + "/" + file_name + ".yml";
    FileStorage Parameters(file, cv::FileStorage::READ);
    Mat P1, P2;

    Parameters["P1"] >> P1;
    Parameters["P2"] >> P2;
    Parameters.release();

    Mat pnts3D(4,1,CV_64FC4);  //retorno
    // Mat cam0pnts(1,1,CV_64FC2, Scalar(100,100));     // matrizes com os pontos das camaras
    // Mat cam1pnts(1,1,CV_64FC2, Scalar(70,100));   // Estes scalar só servem para testar que funciona. Há que testar a veracidade dos valores

    // Inserir código para ler os pontos undistorted recebidos do programa
    cv::triangulatePoints(P1, P2, cam0pnts, cam1pnts, pnts3D);

    cv::FileStorage Points("Points3D.yml", cv::FileStorage::WRITE);  //guarda em ficheiro

    Points << "Points3D Space " << pnts3D << endl;

    return pnts3D;
}
