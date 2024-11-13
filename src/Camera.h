#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
    Camera();
    void setPosition(float x, float y, float z);
    void applyViewTransform();

private:
    float posX, posY, posZ;
};

#endif
