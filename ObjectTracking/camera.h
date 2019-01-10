#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <string>
#include <QDataStream>

using namespace std;

class Camera
{
private:
    string name;
    string IPaddress;
    float xPosition, yPosition, zPosition;
    float pointingAngle;
    bool isCalibratedIntrinsic = false;
    bool isCalibratedExtrinsic = false;
public:
    Camera(string name, string IPaddress, float xPosition, float yPosition, float zPosition, float pointingAngle);
    Camera();
    string getName(void);
    string getIP(void);
    float getX(void);
    float getY(void);
    float getZ(void);
    float getAngle(void);
    uint getIpNumber(void);
    bool isIntrinsicCalibrated(void);
    bool isExtrinsicCalibrated(void);
};

QDataStream &operator<<(QDataStream &out, const Camera &cam);
QDataStream &operator>>(QDataStream &in, Camera &cam);
#endif // CAMERA_H
