#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

class Camera
{
public:
    Camera();
    void setPosition(float x, float y, float z);
    void applyViewTransform();
    void mouseMotion(int x, int y);
    void mouseButton(int button, int state, int x, int y);
    void mouseWheel(int button, int direction, int x, int y);
    void setup();
    void moveForward(float distance);
    void moveBackward(float distance);
    void moveLeft(float distance);
    void moveRight(float distance);
    float getPosX();
    float getPosY();
    float getPosZ();
    float getYaw();
    float getPitch();

    private : float posX,
              posY,
              posZ;
    float pitch;
    float yaw;
    float lastX, lastY;
    bool isLeftButtonPressed;
    float sensitivity;
    bool mouseRotation;
};

#endif
