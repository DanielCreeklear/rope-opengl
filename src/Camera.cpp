#include "Camera.h"
#include <GL/glut.h>

Camera::Camera() : posX(0.0f), posY(0.0f), posZ(5.0f) {}

void Camera::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Camera::applyViewTransform() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
