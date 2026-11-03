#include "Movement.h"
#include <cmath>

bool Movement::updatePosition(float &posX, float &posZ, float deltaTime, float &rotationAngle)
{
    float dx = static_cast<float>(moveRight) - static_cast<float>(moveLeft);
    float dz = static_cast<float>(moveBackward) - static_cast<float>(moveForward);
    const float length = std::sqrt(dx * dx + dz * dz);
    const bool isMoving = length > 0.0f;
    if (isMoving)
    {
        dx /= length;
        dz /= length;
        posX += dx * speed * deltaTime;
        posZ += dz * speed * deltaTime;
        rotationAngle = std::atan2(-dx, -dz) * 180.0f / 3.14159265358979323846f;
    }

    return isMoving;
}
