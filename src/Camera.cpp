#include "Camera.h"
#include <GL/glut.h>
#include <iostream>

Camera::Camera()
    : posX(0.0f), posY(0.0f), posZ(5.0f), isLeftButtonPressed(false),
      yaw(0.0f), pitch(0.0f), lastX(400.0f), lastY(300.0f), sensitivity(0.5f), mouseRotation(true) {}

void Camera::setup()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void Camera::setPosition(float x, float y, float z)
{
    posX = x;
    posY = y;
    posZ = z;
}

void Camera::applyViewTransform()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (mouseRotation)
    {
        float radius = 10.0f;
        float radYaw = yaw * M_PI / 180.0f;
        float radPitch = pitch * M_PI / 180.0f;

        posX = radius * cos(radPitch) * sin(radYaw);
        posY = radius * sin(radPitch);
        posZ = radius * cos(radPitch) * cos(radYaw);

        mouseRotation = false;
    }

    gluLookAt(posX, posY, posZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void Camera::mouseMotion(int x, int y)
{
    if (isLeftButtonPressed)
    {
        mouseRotation = true;
        float deltaX = x - lastX;
        float deltaY = y - lastY;

        yaw += deltaX * -sensitivity;
        pitch -= deltaY * -sensitivity;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    lastX = x;
    lastY = y;
}

void Camera::mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        isLeftButtonPressed = !isLeftButtonPressed;
    }
}

void Camera::moveForward(float distance)
{
    float radYaw = yaw * M_PI / 180.0f;
    float radPitch = pitch * M_PI / 180.0f;

    posX += distance * cos(radPitch) * sin(radYaw);
    posY += distance * sin(radPitch);
    posZ += distance * cos(radPitch) * cos(radYaw);
}

void Camera::moveBackward(float distance)
{
    moveForward(-distance);
}

void Camera::moveLeft(float distance)
{
    float radYaw = (yaw + 90.0f) * M_PI / 180.0f;
    posX += distance * sin(radYaw);
    posZ += distance * cos(radYaw);
}

void Camera::moveRight(float distance)
{
    moveLeft(-distance);
}

float Camera::getPosX()
{
    return posX;
}

float Camera::getPosY()
{
    return posY;
}

float Camera::getPosZ()
{
    return posZ;
}

float Camera::getYaw()
{
    return yaw;
}

float Camera::getPitch()
{
    return pitch;
}