#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "camera.h"

Camera::Camera(string name, string IPaddress, float xPosition, float yPosition, float zPosition, float pointingAngle)
{
    this->name = name;
    this->IPaddress = IPaddress;
    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->zPosition = zPosition;
    this->pointingAngle = pointingAngle;
}

Camera::Camera()
{
    this->name = "";
    this->IPaddress = "";
    this->xPosition = 0;
    this->yPosition = 0;
    this->zPosition = 0;
    this->pointingAngle = 0;
}

string Camera::getName(void)
{
    return this->name;
}

string Camera::getIP(void)
{
    return this->IPaddress;
}

float Camera::getX(void)
{
    return this->xPosition;
}

float Camera::getY(void)
{
    return this->yPosition;
}

float Camera::getZ(void)
{
    return this->zPosition;
}

float Camera::getAngle(void)
{
    return this->pointingAngle;
}

// Converts IP in string format to decimal format
uint Camera::getIpNumber(void)
{
    struct sockaddr_in ip4addr;

    ip4addr.sin_family = AF_INET;
    inet_pton(AF_INET, this->getIP().c_str(), &ip4addr.sin_addr);

    return htonl(ip4addr.sin_addr.s_addr);
}

QDataStream &operator<<(QDataStream &out, const Camera &cam)
{
    out.writeRawData(reinterpret_cast<const char*>(&cam), sizeof(cam));
    return out;
}

QDataStream &operator>>(QDataStream &in, Camera &cam)
{
    in.readRawData(reinterpret_cast<char*>(&cam), sizeof(cam));
    return in;
}
