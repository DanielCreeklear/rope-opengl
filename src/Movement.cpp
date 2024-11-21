#include "Movement.h"

bool Movement::updatePosition(float &posX, float &posZ, float deltaTime, float &rotationAngle)
{
    const bool isMoving = moveForward || moveBackward || moveLeft || moveRight;

    if (moveForward)
    {
        posZ -= speed * deltaTime;
        rotationAngle = 0.0f;
    }
    if (moveBackward)
    {
        posZ += speed * deltaTime;
        rotationAngle = 180.0f;
    }
    if (moveLeft)
    {
        posX -= speed * deltaTime;
        rotationAngle = 90.0f;
    }
    if (moveRight)
    {
        posX += speed * deltaTime;
        rotationAngle = -90.0f;
    }

    return isMoving;
}