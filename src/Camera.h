#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <cmath>

class Camera
{
public:
    Camera();
    void setup();
    void applyViewTransform(float characterX, float characterY, float characterZ);

    void mouseMotion(int x, int y);
    void mouseButton(int button, int state, int x, int y);
    void mouseWheel(int button, int direction, int x, int y);

private:
    float posX, posY, posZ;
    float yaw, pitch;
    float sensitivity;
    bool mouseRotation;

    float cameraOffsetX, cameraOffsetY, cameraOffsetZ;
};

#endif
