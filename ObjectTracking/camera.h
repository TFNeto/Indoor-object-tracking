#ifndef CAMERA_H
#define CAMERA_H
#include <stdio.h>
#include <string>
class Camera
{
private:
    std::string name;
    std::string IPaddress;
    float xPosition, yPosition, zPosition;
    float pointingAngle;
public:
    Camera(std::string name, std::string IPaddress, float xPosition, float yPosition, float zPosition, float pointingAngle);
    std::string getName(void);
    std::string getIP(void);
    float getX(void);
    float getY(void);
    float getZ(void);
    float getAngle(void);
};

#endif // CAMERA_H
