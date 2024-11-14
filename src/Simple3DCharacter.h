#ifndef SIMPLE_3D_CHARACTER_H
#define SIMPLE_3D_CHARACTER_H

#include <GL/glut.h>
#include <cmath>

class Simple3DCharacter
{
public:
    Simple3DCharacter(float scale, float torsoHeight, float headRadius, float limbLength, float limbWidth);
    void draw() const;
    void update(float deltaTime);

private:
    float scale;
    float armRotationAngle;
    float legRotationAngle;
    float headRotationAngle;

    float torsoHeight;
    float headRadius;
    float limbLength;
    float limbWidth;

    void drawTorso() const;
    void drawHead() const;
    void drawLimbsWithDetails() const;
    void drawLimb(float length, float width, float xOffset, float yOffset, float zOffset, float rotationAngle) const;
    void drawAdditionalComponents() const;
    void rotateWithLimits(float &angle, float &speed, float minAngle, float maxAngle, float deltaTime);
};

#endif
