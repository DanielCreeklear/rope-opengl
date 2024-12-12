#ifndef SIMPLE_3D_CHARACTER_H
#define SIMPLE_3D_CHARACTER_H

#include <GL/glut.h>
#include <cmath>
#include "stb_image.h"

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
    void loadTexture(const char *filename, GLuint *textureID);

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

    void increaseAngleLeftArm(float angle);
    void increaseAngleRightArm(float angle);
    void increaseAngleLeftLeg(float angle);
    void increaseAngleRightLeg(float angle);

    void setIdle(bool state);
    
    void init();

private:
    float scale;

    float torsoHeight;
    float headRadius;
    float limbLength;
    float limbWidth;

    float posX, posY, posZ;

    bool isWalking, enableIdle;

    Animator *animator;
    Physics *physics;
    Movement *movement;

    GLuint textureIDTorso;
    GLuint textureIDHead;
    GLuint textureIDLimb;
    GLuint textureIds[3];

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
