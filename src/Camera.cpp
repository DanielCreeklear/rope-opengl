#include "Camera.h"
#include <GL/glut.h>

Camera::Camera()
    : cameraOffsetX(0.0f), cameraOffsetY(10.0f), cameraOffsetZ(30.0f), mouseRotation(false) {}

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

void Camera::applyViewTransform(float characterX, float characterY, float characterZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float targetPosX = characterX + cameraOffsetZ * cos(yaw);
    float targetPosY = characterY + cameraOffsetY;
    float targetPosZ = characterZ + cameraOffsetZ * sin(yaw);

    posX += (targetPosX - posX) * 0.1f;
    posY += (targetPosY - posY) * 0.1f;
    posZ += (targetPosZ - posZ) * 0.1f;

    gluLookAt(posX, posY, posZ, characterX, characterY, characterZ, 0.0f, 1.0f, 0.0f);
}

void Camera::mouseMotion(int x, int y)
{
    if (mouseRotation) // Só gira se o botão esquerdo estiver pressionado
    {
        int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
        int deltaX = x - centerX;

        float sensitivity = 0.005f;

        yaw += deltaX * sensitivity;

        glutWarpPointer(centerX, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    }
}

void Camera::mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseRotation = !mouseRotation;
    }
}

void Camera::mouseWheel(int button, int direction, int x, int y) {}
