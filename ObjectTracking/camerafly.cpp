#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

#include "camerafly.h"
#include "camera.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

// "Global" camera object used in several methods
// WIP: We'll probably need 4 of these for the normal mode
/*FlyCapture2::GigECamera cam;
FlyCapture2::GigECamera cam1;
FlyCapture2::GigECamera cam2;
FlyCapture2::GigECamera cam3;*/
FlyCapture2::GigECamera *lista ;
unsigned int numCamInfo = 10;

// Utility function to print FlyCapture errors
void PrintError(FlyCapture2::Error error) { error.PrintErrorTrace(); }

// This function is only for debug purposes. Prints all information about a camera.
void PrintCameraInfo(FlyCapture2::CameraInfo *pCamInfo)
{
    ostringstream macAddress;
    macAddress << hex << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[0]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[1]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[2]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[3]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[4]) << ":" << hex
               << setw(2) << setfill('0')
               << static_cast<unsigned int>(pCamInfo->macAddress.octets[5]);

    ostringstream ipAddress;
    ipAddress << static_cast<unsigned int>(pCamInfo->ipAddress.octets[0]) << "."
              << static_cast<unsigned int>(pCamInfo->ipAddress.octets[1]) << "."
              << static_cast<unsigned int>(pCamInfo->ipAddress.octets[2]) << "."
              << static_cast<unsigned int>(pCamInfo->ipAddress.octets[3]);

    ostringstream subnetMask;
    subnetMask << static_cast<unsigned int>(pCamInfo->subnetMask.octets[0]) << "."
               << static_cast<unsigned int>(pCamInfo->subnetMask.octets[1]) << "."
               << static_cast<unsigned int>(pCamInfo->subnetMask.octets[2]) << "."
               << static_cast<unsigned int>(pCamInfo->subnetMask.octets[3]);

    ostringstream defaultGateway;
    defaultGateway << static_cast<unsigned int>(pCamInfo->defaultGateway.octets[0]) << "."
                   << static_cast<unsigned int>(pCamInfo->defaultGateway.octets[1]) << "."
                   << static_cast<unsigned int>(pCamInfo->defaultGateway.octets[2]) << "."
                   << static_cast<unsigned int>(pCamInfo->defaultGateway.octets[3]);

    cout << endl;
    cout << "*** CAMERA INFORMATION ***" << endl;
    cout << "Serial number - " << pCamInfo->serialNumber << endl;
    cout << "Camera model - " << pCamInfo->modelName << endl;
    cout << "Camera vendor - " << pCamInfo->vendorName << endl;
    cout << "Sensor - " << pCamInfo->sensorInfo << endl;
    cout << "Resolution - " << pCamInfo->sensorResolution << endl;
    cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
    cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl;
    cout << "GigE version - " << pCamInfo->gigEMajorVersion << "."
         << pCamInfo->gigEMinorVersion << endl;
    cout << "User defined name - " << pCamInfo->userDefinedName << endl;
    cout << "XML URL 1 - " << pCamInfo->xmlURL1 << endl;
    cout << "XML URL 2 - " << pCamInfo->xmlURL2 << endl;
    cout << "MAC address - " << macAddress.str() << endl;
    cout << "IP address - " << ipAddress.str() << endl;
    cout << "Subnet mask - " << subnetMask.str() << endl;
    cout << "Default gateway - " << defaultGateway.str() << endl << endl;
}

// Scan (GIGE) cameras. Returns a vector of Camera objects, or an empty vector if none was found.
vector<Camera> scanCameras()
{
    vector<Camera> listOfCameras;

    FlyCapture2::Error error;
    FlyCapture2::BusManager busMgr;

    FlyCapture2::CameraInfo camInfo[10];
    FlyCapture2::CameraInfo nova;



    // Scan for GIGE cameras
    error = FlyCapture2::BusManager::DiscoverGigECameras(camInfo, &numCamInfo);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return vector<Camera>();
    }

    cout << "DEBUG: Number of GigE cameras discovered: " << numCamInfo << endl;

    if (numCamInfo == 0)
    {
        // No cameras found
        cout << "DEBUG: No suitable GigE cameras found. Press Enter to exit..." << endl;
        return vector<Camera>();
    }
    lista = new FlyCapture2::GigECamera[numCamInfo];
    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        //PrintCameraInfo(&camInfo[i]); // DEBUG
        ostringstream ipAddress;
        ipAddress << static_cast<unsigned int>(camInfo[i].ipAddress.octets[0]) << "."
                  << static_cast<unsigned int>(camInfo[i].ipAddress.octets[1]) << "."
                  << static_cast<unsigned int>(camInfo[i].ipAddress.octets[2]) << "."
                  << static_cast<unsigned int>(camInfo[i].ipAddress.octets[3]);
        // Create Camera obj and add it to the listOfCameras vector
        listOfCameras.push_back(Camera(camInfo->modelName, ipAddress.str(), 0, 0, 0, 0));

        FlyCapture2::PGRGuid *guid;
        error = busMgr.GetCameraFromIndex(i, guid);

            error =lista[i].Connect(guid);
            if (error != FlyCapture2::PGRERROR_OK)
            {
                PrintError(error);
                return vector<Camera>();
            }
            error =lista[i].GetCameraInfo(&nova);
            if (error != FlyCapture2::PGRERROR_OK)
            {
                PrintError(error);
                return vector<Camera>();
            }
            PrintCameraInfo(&nova);
            // Disconnect the camera
            error = lista[i].Disconnect();
            if (error != FlyCapture2::PGRERROR_OK)
            {
                PrintError(error);
                cout<< "Failed to disconnect camera"<<endl;
            }


    }
    return listOfCameras;
}
void startRecording(int index)
{
    FlyCapture2::Error error;
    // Start capturing images
    error = lista[index].StartCapture();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<< "Failed to start"<<endl;;
    }
}
void stopRecording(int index)
{
    FlyCapture2::Error error;

    // Stop capturing images
    error =  lista[index].StopCapture();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<< "Failed to stop capturing images"<<endl;
    }
}
int connectToCameraByIp(FlyCapture2::IPAddress ipAddress)
{
    FlyCapture2::Error error;
    FlyCapture2::BusManager busMgr;
    FlyCapture2::PGRGuid guid1,guid ;
    FlyCapture2::CameraInfo *temp;
    int index=0;

    error = busMgr.GetCameraFromIPAddress(ipAddress, &guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<< "Couldn't get camera"<<endl;
    }
    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        error = busMgr.GetCameraFromIndex(i, &guid1);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
            cout<< "Couldn't get camera"<<endl;
        }

        if(guid1==guid)
        {

            index=i;
            cout<<"index ="<<index<<endl;
        }
    }

    cout<<"connecting to cam" <<endl;
    // Connect to a camera
    // FlyCapture2::GigECamera cam;
    error = lista[index].Connect(&guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<< "Failed to connect to camera"<<endl;
    }

    cout << "DEBUG: Starting image capture..." << endl;

    // Start capturing images
    error = lista[index].StartCapture();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
       cout<< "Failed to start"<<endl;
    }
    return index;
}

// Disconnects a single camera
// Assumes that the camera was connected
// Uses the "global" cam object, which is why there are no arguments
void disconnectCameraByIp(FlyCapture2::IPAddress ipAddress)
{
    FlyCapture2::BusManager busMgr;
    FlyCapture2::Error error;
    FlyCapture2::PGRGuid guid1,guid ;
    FlyCapture2::CameraInfo *temp;
    int index=0;

    error = busMgr.GetCameraFromIPAddress(ipAddress, &guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<< "Couldn't get camera"<<endl;
    }
    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        error = busMgr.GetCameraFromIndex(i, &guid1);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
            cout<< "Couldn't get camera"<<endl;
        }

        if(guid1==guid)
        {

            index=i;
            cout<<"index ="<<index<<endl;
        }
    }
    // Stop capturing images
    error =  lista[index].StopCapture();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<< "Failed to stop capturing images"<<endl;
    }

    // Disconnect the camera
    error = lista[index].Disconnect();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<< "Failed to disconnect camera"<<endl;
    }
}

// Takes a single picture from a single camera
// Assumes that the camera is already connected
// Uses the "global" cam object, which is why there are no arguments
FlyCapture2::Image takeSinglePictureFromSingleCamera(int index)
{
    FlyCapture2::Error error;
    FlyCapture2::Image rawImage;
    FlyCapture2::Image convertedImage;

    // Retrieve an image
    error = lista[index].RetrieveBuffer(&rawImage);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<< "Failed to retrieve buffer"<<endl;
    }

    //cout << "DEBUG: Grabbed image" << endl;

    // Convert the raw image
    error = rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &convertedImage);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<<"Failde to convert" <<endl;
    }

    return convertedImage;
}

// Saves an image in png format
void saveImage(FlyCapture2::Image img, string camIp, int imgNum)
{
    string fileName = "calib" + camIp + "_" + to_string(imgNum) + ".png";
    FlyCapture2::Error error;
    error = img.Save(fileName.c_str());
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
    }
    cout << "DEBUG: Image saved " + fileName << endl;
}
