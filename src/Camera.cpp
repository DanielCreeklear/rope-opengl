#include "Camera.h"
#include <iostream>

Camera::Camera()
    : cameraOffsetX(0.0f), cameraOffsetY(10.0f), cameraOffsetZ(30.0f), mouseRotation(false) {}

void Camera::setup()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void Camera::applyViewTransform(float characterX, float characterY, float characterZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float offsetX = cameraOffsetZ * cos(pitch) * sin(yaw);
    float offsetY = cameraOffsetZ * sin(pitch) + cameraOffsetY;
    float offsetZ = cameraOffsetZ * cos(pitch) * cos(yaw);

    posX = characterX + offsetX;
    posY = characterY + offsetY;
    posZ = characterZ + offsetZ;

    std::cout << "Camera offset: (" << offsetX << ", " << offsetY << ", " << offsetZ << ")" << std::endl;
    // std::cout << "Camera pos: (" << posX << ", " << posY << ", " << posZ << ")" << std::endl;

    gluLookAt(posX, posY, posZ, characterX, characterY, characterZ, 0.0f, 1.0f, 0.0f);
}

void Camera::mouseMotion(int x, int y)
{
    sensitivity = 0.01f;
    if (mouseRotation)
    {
        int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
        int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

        int deltaX = x - centerX;
        int deltaY = y - centerY;

        yaw += deltaX * sensitivity;
        pitch -= deltaY * sensitivity;

        if (pitch > 1.5f)
            pitch = 1.5f;
        if (pitch < -1.5f)
            pitch = -1.5f;

        glutWarpPointer(centerX, centerY);
    }
}

void Camera::mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseRotation = !mouseRotation;
    }
}

void Camera::mouseWheel(int button, int direction, int x, int y)
{
    if (direction > 0)
        cameraOffsetZ -= 1.0f;
    else
        cameraOffsetZ += 1.0f;

    if (cameraOffsetZ < 5.0f)
        cameraOffsetZ = 5.0f;
    if (cameraOffsetZ > 50.0f)
        cameraOffsetZ = 50.0f;
}
