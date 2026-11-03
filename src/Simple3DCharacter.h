#ifndef SIMPLE_3D_CHARACTER_H
#define SIMPLE_3D_CHARACTER_H

#include <GL/glut.h>
#include <cmath>
#include <memory>
#include "Texture.h"
#include "Physics.h"

class Animator;
class Movement;
class Terrain;
class BouncingBall;

class Simple3DCharacter
{
public:
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
    ~Simple3DCharacter();
    Simple3DCharacter(const Simple3DCharacter &) = delete;
    Simple3DCharacter &operator=(const Simple3DCharacter &) = delete;
    void draw() const;
    void update(float deltaTime, const Terrain &terrain, BouncingBall &ball);

    void startWalking();
    void stopWalking();
    void move(float deltaTime);
    void jump();

    float getPosX() const;
    float getPosY() const;
    float getPosZ() const;
    float getFootHeight() const;

    void setMoveForward(bool value);
    void setMoveBackward(bool value);
    void setMoveLeft(bool value);
    void setMoveRight(bool value);
    bool hasMovementInput() const;

    void increaseAngleLeftArm(float angle);
    void increaseAngleRightArm(float angle);
    void increaseAngleLeftLeg(float angle);
    void increaseAngleRightLeg(float angle);

    void setIdle(bool state);
    void startCelebration(bool state);

    void resetCharacter();
    void kickBall(BouncingBall &ball);
    bool checkCollisionWithBall(BouncingBall &ball);
    float calculateRadius() const;

    void init();
    void releaseGraphicsResources();

private:
    float scale;

    float torsoHeight;
    float headRadius;
    float limbLength;
    float limbWidth;

    Physics physics;

    bool isWalking, enableIdle, celebration;
    bool ballContact;

    std::unique_ptr<Animator> animator;
    std::unique_ptr<Movement> movement;

    GLuint textureIDTorso;
    GLuint textureIDHead;
    std::unique_ptr<GLUquadric, decltype(&gluDeleteQuadric)> headQuadric;

    void drawLeftArm() const;
    void drawRightArm() const;
    void drawLeftLeg() const;
    void drawRightLeg() const;
    void drawForearm(float length, float width, float rotationAngle) const;
    void drawCalf(float length, float width, float rotationAngle) const;
    void drawTorso() const;
    void drawHead() const;
    void drawLimbsWithDetails() const;
    void drawLimb(float length, float width, float xOffset, float yOffset, float zOffset, float rotationAngle) const;
    void drawTexturedCylinder(float radius, float height, int slices, int stacks) const;

    void drawAdditionalComponents() const;
    void setMaterial(const float ambient[4], const float diffuse[4], const float specular[4], float shininess) const;

    void updateRotation(char direction);
};

#endif
