#include "Camera.h"
#include <iostream>

Camera::Camera()
    : posX(0.0f), posY(0.0f), posZ(0.0f), yaw(0.0f), pitch(0.25f), sensitivity(0.01f), mouseRotation(false),
      cameraOffsetX(0.0f), cameraOffsetY(10.0f), cameraOffsetZ(30.0f), viewportWidth(800), viewportHeight(600) {}

void Camera::setup(int width, int height)
{
    reshape(width, height);
}

void Camera::reshape(int width, int height)
{
    viewportWidth = width > 0 ? width : 1;
    viewportHeight = height > 0 ? height : 1;
    glViewport(0, 0, viewportWidth, viewportHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(viewportWidth) / viewportHeight, 0.1f, 250.0f);

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

    gluLookAt(posX, posY, posZ, characterX, characterY, characterZ, 0.0f, 1.0f, 0.0f);
}

void Camera::mouseMotion(int x, int y)
{
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

void Camera::mouseButton(int button, int state, int, int)
{
    if (button == GLUT_MIDDLE_BUTTON)
    {
        mouseRotation = (state == GLUT_DOWN);
    }
}

void Camera::mouseWheel(int, int direction, int, int)
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
