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

unsigned int numCamInfo = 10;
FlyCapture2::GigECamera *lista;

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

        FlyCapture2::PGRGuid guid;
        error = busMgr.GetCameraFromIndex(i, &guid);
        // Connect to Camera
        error = lista[i].Connect(&guid);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
        }
        // Get its info
        error = lista[i].GetCameraInfo(&nova);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
        }
        PrintCameraInfo(&nova);
        // Disconnect the camera
        error = lista[i].Disconnect();
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
            cout << "Failed to disconnect camera" << endl;
        }
    }
    return listOfCameras;
}

/*
* Connects to a camera by IP
* @param FlyCapture2::IPAddress ipAddress - camera's ip address
* @param char mode - Operating mode (s for external trigger)
* @return int - Camera's index
*/
int connectToCameraByIp(FlyCapture2::IPAddress ipAddress, char mode)
{
    FlyCapture2::Error error;
    FlyCapture2::BusManager busMgr;
    FlyCapture2::PGRGuid guid1,guid ;
    unsigned int index = 0;

    error = busMgr.GetCameraFromIPAddress(ipAddress, &guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout << "Couldn't get camera" << endl;
    }
    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        error = busMgr.GetCameraFromIndex(i, &guid1);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
            cout << "Couldn't get camera" << endl;
            cin.ignore();
            return -1;
        }

        if(guid1 == guid)
        {
            index = i;
            cout << "index = " << index << endl;
        }
    }

    // Connect to a camera
    error = lista[index].Connect(&guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout<< "Failed to connect to camera"<<endl;
    }

    FlyCapture2::TriggerModeInfo TriggerModeInfo;
    FlyCapture2::TriggerMode triggerMode;

    if(mode == 's')
    {
        triggerMode.mode = 14;
        triggerMode.onOff = true;
        triggerMode.polarity = 0;
        triggerMode.source = 0; // GPIO pin
    }
    else
    {
        triggerMode.onOff = false;
        triggerMode.mode = 0;
    }

    error = lista[index].SetTriggerMode(&triggerMode);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout << "Failed to Set trigger mode" << endl;
        return -1;
    }

    // Turn Timestamp on
    FlyCapture2::EmbeddedImageInfo imageInfo;
    imageInfo.timestamp.onOff = true;
    error = lista[index].SetEmbeddedImageInfo(&imageInfo);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout << "Failed to set timestamp" << endl;
        return -1;
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

/*
* Disconnects a camera by IP
* @param FlyCapture2::IPAddress ipAddress - Camera's IP Address
*/
void disconnectCameraByIp(FlyCapture2::IPAddress ipAddress)
{
    FlyCapture2::BusManager busMgr;
    FlyCapture2::Error error;
    FlyCapture2::PGRGuid guid1,guid ;
    unsigned int index = 0;

    error = busMgr.GetCameraFromIPAddress(ipAddress, &guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout << "Couldn't get camera" << endl;
    }
    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        error = busMgr.GetCameraFromIndex(i, &guid1);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
            cout << "Couldn't get camera" << endl;
        }

        if(guid1 == guid)
        {
            index = i;
            cout << "index =" << index << endl;
        }
    }
    // Stop capturing images
    error = lista[index].StopCapture();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout << "Failed to stop capturing images" << endl;
    }

    // Disconnect the camera
    error = lista[index].Disconnect();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout << "Failed to disconnect camera" << endl;
    }
}

/*
* Takes a single picture from a single camera
* @param int index - Camera's index
* @return FlyCapture2::Image - image, converted to BGR
*/
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
        cout << "Failed to retrieve buffer" << endl;
    }

    cout << "DEBUG: Grabbed image" << endl;

    // Convert the raw image
    error = rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &convertedImage);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        cout << "Failed to convert" << endl;
    }

    return convertedImage;
}

// Saves an image in png format
// @param FlyCapture2::Image img - the image itself
// @param string camIp - Camera's ip (for the filename)
// @param imgNum - Image number (Asc order, for the filename)
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

void connectAllCameras()
{
    FlyCapture2::Error error;
    FlyCapture2::BusManager busMgr;
    FlyCapture2::CameraInfo camInfo[10];
    FlyCapture2::PGRGuid guid;

    // Scan for GIGE cameras
    error = FlyCapture2::BusManager::DiscoverGigECameras(camInfo, &numCamInfo);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
    }
    cout<<"Were discovered : "<<numCamInfo<<" cameras"<<endl;

    lista = new FlyCapture2::GigECamera[numCamInfo];
    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        error = busMgr.GetCameraFromIndex(i, &guid);
        // Connect to Camera
        error = lista[i].Connect(&guid);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
        }
        FlyCapture2::TriggerModeInfo TriggerModeInfo;
        FlyCapture2::TriggerMode triggerMode;


        triggerMode.mode = 14;
        triggerMode.onOff = true;
        triggerMode.polarity = 0;
        triggerMode.source = 0; // GPIO pin

        error = lista[i].SetTriggerMode(&triggerMode);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
            cout << "Failed to Set trigger mode" << endl;
        }

        // Turn Timestamp on
        FlyCapture2::EmbeddedImageInfo imageInfo;
        imageInfo.timestamp.onOff = true;
        error = lista[i].SetEmbeddedImageInfo(&imageInfo);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
            cout << "Failed to set timestamp" << endl;
        }
    }
    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        error = lista[i].StartCapture();
        if (error != FlyCapture2::PGRERROR_OK)
        {
            PrintError(error);
            cout<< "Failed to start"<<endl;
        }
    }
}
