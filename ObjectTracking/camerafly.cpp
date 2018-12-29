#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

#include "camerafly.h"
#include "camera.h"

using namespace std;

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
    unsigned int numCamInfo = 10;

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

    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        PrintCameraInfo(&camInfo[i]); // DEBUG
        ostringstream ipAddress;
        ipAddress << static_cast<unsigned int>(camInfo->ipAddress.octets[0]) << "."
                  << static_cast<unsigned int>(camInfo->ipAddress.octets[1]) << "."
                  << static_cast<unsigned int>(camInfo->ipAddress.octets[2]) << "."
                  << static_cast<unsigned int>(camInfo->ipAddress.octets[3]);
        // Create Camera obj and add it to the listOfCameras vector
        listOfCameras.push_back(Camera(camInfo->modelName, ipAddress.str(), 0, 0, 0, 0));
    }

    return listOfCameras;
}

string takeSinglePictureFromSingleCamera(FlyCapture2::IPAddress ipAddress)
{
    FlyCapture2::Error error;
    FlyCapture2::BusManager busMgr;
    FlyCapture2::PGRGuid guid;

    // FlyCapture2::IPAddress();
    error = busMgr.GetCameraFromIPAddress(ipAddress, &guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return nullptr;
    }

    // Connect to a camera
    FlyCapture2::GigECamera cam;
    error = cam.Connect(&guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return nullptr;
    }

    cout << "Starting image capture..." << endl;

    // Start capturing images
    error = cam.StartCapture();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return nullptr;
    }

    FlyCapture2::Image rawImage;
    FlyCapture2::Image convertedImage;

    // Retrieve an image
    error = cam.RetrieveBuffer(&rawImage);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return nullptr;
    }

    cout << "Grabbed image " << endl;

    // Convert the raw image
    error = rawImage.Convert(FlyCapture2::PIXEL_FORMAT_RGBU, &convertedImage);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return nullptr;
    }

    // ostringstream filename;

    string filename = "teste" + to_string(rand() % 100) + ".png";
    /*
    filename << "FlyCapture2Test-" << camInfo.serialNumber << "-"
             << imageCnt << ".png";
    */

    // Save the image. If a file format is not passed in, then the file
    // extension is parsed to attempt to determine the file format.
    //error = convertedImage.Save(filename.str().c_str());
    error = convertedImage.Save(filename.c_str());
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return nullptr;
    }

    cout << "Stopping capture" << endl;

    // Stop capturing images
    error = cam.StopCapture();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return nullptr;
    }

    // Disconnect the camera
    error = cam.Disconnect();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        PrintError(error);
        return nullptr;
    }
    return filename;
}
