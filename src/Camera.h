#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>

class Camera
{
public:
    Camera();
    void setup();
    void setPosition(float x, float y, float z);
    void applyViewTransform();

    void mouseMotion(int x, int y);
    void mouseButton(int button, int state, int x, int y);
    void mouseWheel(int button, int direction, int x, int y);

    void moveForward(float distance);
    void moveBackward(float distance);
    void moveLeft(float distance);
    void moveRight(float distance);

    float getPosX();
    float getPosY();
    float getPosZ();
    float getYaw();
    float getPitch();

private:
    float posX, posY, posZ;
    bool isLeftButtonPressed;

    float yaw, pitch;
    float lastX, lastY;
    float sensitivity;
    bool mouseRotation;

    float cameraOffsetX, cameraOffsetY, cameraOffsetZ;
};

#endif
