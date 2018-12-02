#include "camera.h"

Camera::Camera(std::string name, std::string IPaddress, float xPosition, float yPosition, float zPosition, float pointingAngle)
{
    this->name = name;
    this->IPaddress = IPaddress;
    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->zPosition = zPosition;
    this->pointingAngle = pointingAngle;
}

std::string Camera::getName(void) {
    return this->name;
}
std::string Camera::getIP(void){
    return this->IPaddress;
}
float Camera::getX(void){
    return this->xPosition;
}
float Camera::getY(void){
    return this->yPosition;
}
float Camera::getZ(void){
    return this->zPosition;
}
float Camera::getAngle(void) {
    return this->pointingAngle;
}
