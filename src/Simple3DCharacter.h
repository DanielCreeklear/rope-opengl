#ifndef SIMPLE_3D_CHARACTER_H
#define SIMPLE_3D_CHARACTER_H

#include <GL/glut.h>
#include <cmath>

class Animator;
class Physics;
class Movement;
class Terrain;

class Simple3DCharacter
{
public:
    bool moveForward, moveBackward, moveLeft, moveRight;

    float rotationAngleCharacter;
    float armRightRotationAngle;
    float armLeftRotationAngle;
    float directionRightArmRotation;
    float directionLeftArmRotation;
    float directionTorsoRotation;

    float legLeftRotationAngle;
    float legRightRotationAngle;
    float directionLeftLegRotation;
    float directionRightLegRotation;
    float torsoRotationAngle;

    float headRotationAngle;
    float directionHeadRotation;

    Simple3DCharacter(float scale, float torsoHeight, float headRadius, float limbLength, float limbWidth);
    void draw() const;
    void update(float deltaTime, const Terrain &terrain);

    void startWalking();
    void stopWalking();
    void move(float deltaTime);
    void jump();

    float getPosX();
    float getPosY();
    float getPosZ();
    float getFootHeight() const;

    void setMoveForward(bool value);
    void setMoveBackward(bool value);
    void setMoveLeft(bool value);
    void setMoveRight(bool value);

private:
    float scale;

    float torsoHeight;
    float headRadius;
    float limbLength;
    float limbWidth;

    float posX, posY, posZ;

    bool isWalking;

    Animator *animator;
    Physics *physics;
    Movement *movement;

    void drawLeftArm() const;
    void drawRightArm() const;
    void drawLeftLeg() const;
    void drawRightLeg() const;
    void drawTorso() const;
    void drawHead() const;
    void drawLimbsWithDetails() const;
    void drawLimb(float length, float width, float xOffset, float yOffset, float zOffset, float rotationAngle) const;
    void drawAdditionalComponents() const;

    void updateRotation(char direction);
};

#endif
