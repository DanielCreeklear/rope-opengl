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

    void startWalking();
    void stopWalking();

private: 
    float scale;
    float armRightRotationAngle;
    float armLeftRotationAngle;
    float directionRightArmRotation;
    float directionLeftArmRotation;

    float legLeftRotationAngle;
    float legRightRotationAngle;
    float directionLeftLegRotation;
    float directionRightLegRotation;

    float headRotationAngle;
    float directionHeadRotation;

    float torsoHeight;
    float headRadius;
    float limbLength;
    float limbWidth;

    bool isWalking;

    void drawLeftArm() const;
    void drawRightArm() const;
    void drawLeftLeg() const;
    void drawRightLeg() const;
    void drawTorso() const;
    void drawHead() const;
    void drawLimbsWithDetails() const;
    void drawLimb(float length, float width, float xOffset, float yOffset, float zOffset, float rotationAngle) const;
    void drawAdditionalComponents() const;

    void rotateWithLimits(float &angle, float speed, float &direction, float minAngle, float maxAngle, float deltaTime);

    void walkAnimation(float deltaTime);
};

#endif
