#include "Simple3DCharacter.h"
#include "Cylinder.h"
#include "Animator.h"
#include "Physics.h"
#include "stb_image.h"
#include "Movement.h"
#include "Terrain.h"
#include "SolidCube.h"
#include <algorithm>

Simple3DCharacter::Simple3DCharacter(float scale, float torsoHeight, float headRadius, float limbLength, float limbWidth)
    : scale(scale), torsoHeight(torsoHeight), headRadius(headRadius), limbLength(limbLength), limbWidth(limbWidth),
      armLeftRotationAngle(0.0f), armRightRotationAngle(0.0f), legLeftRotationAngle(0.0f), legRightRotationAngle(0.0f),
      torsoRotationAngle(0.0f), headRotationAngle(0.0f), directionRightArmRotation(1.0f), directionLeftArmRotation(-1.0f), directionLeftLegRotation(1.0f),
      directionRightLegRotation(-1.0f), directionHeadRotation(1.0f), directionTorsoRotation(1.0f), isWalking(false),
      moveForward(false), moveBackward(false), moveLeft(false), moveRight(false), posX(0.0f), posZ(0.0f), rotationAngleCharacter(0.0f)
{
    animator = new Animator(this);
    physics = new Physics(-16.8f, 0.8f, 0.0f, 10.0f);
    movement = new Movement(10.0f);
    posY = 10.0f;

    loadTexture("pelo.png", textureIDTorso);
}

void Simple3DCharacter::loadTexture(const char* filename, GLuint* textureID)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    if (data)
    {
        glGenTextures(1, textureID);
        glBindTExture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMA_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
}

void Simple3DCharacter::drawHead() const
{
    glPushMatrix();

    glTranslatef(0.0f, torsoHeight + headRadius, 0.0f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glutSolidSphere(headRadius, 10, 10);

    glTranslatef(0.0f, headRadius, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCone(0.5f, headRadius * 1.5f, 10, 10);
    glPopMatrix();
}

void Simple3DCharacter::drawTorso() const
{
    glPushMatrix();
    glTranslatef(0.0f, torsoHeight / 2.0f, 0.0f);
    glRotatef(torsoRotationAngle, 0.0f, 1.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDTorso);

    glBegin(GLU_BEGIN);    
    drawQuadFace(-torsoHeight / 2, -torsoHeight / 2, torsoHeight / 2,
                 torsoHeight / 2, -torsoHeight / 2, torsoHeight / 2,
                 torsoHeight / 2, torsoHeight / 2, torsoHeight / 2,
                 -torsoHeight / 2, torsoHeight / 2, torsoHeight / 2);
    
    drawQuadFace(-torsoHeight / 2, -torsoHeight / 2, -torsoHeight / 2,
                 torsoHeight / 2, -torsoHeight / 2, -torsoHeight / 2,
                 torsoHeight / 2, torsoHeight / 2, -torsoHeight / 2,
                 -torsoHeight / 2, torsoHeight / 2, -torsoHeight / 2);
    
    drawQuadFace(-torsoHeight / 2, -torsoHeight / 2, -torsoHeight / 2,
                 -torsoHeight / 2, -torsoHeight / 2, torsoHeight / 2,
                 -torsoHeight / 2, torsoHeight / 2, torsoHeight / 2,
                 -torsoHeight / 2, torsoHeight / 2, -torsoHeight / 2);
    
    drawQuadFace(torsoHeight / 2, -torsoHeight / 2, -torsoHeight / 2,
                 torsoHeight / 2, -torsoHeight / 2, torsoHeight / 2,
                 torsoHeight / 2, torsoHeight / 2, torsoHeight / 2,
                 torsoHeight / 2, torsoHeight / 2, -torsoHeight / 2);
    
    drawQuadFace(-torsoHeight / 2, torsoHeight / 2, -torsoHeight / 2,
                 torsoHeight / 2, torsoHeight / 2, -torsoHeight / 2,
                 torsoHeight / 2, torsoHeight / 2, torsoHeight / 2,
                 -torsoHeight / 2, torsoHeight / 2, torsoHeight / 2);
    
    drawQuadFace(-torsoHeight / 2, -torsoHeight / 2, -torsoHeight / 2,
                 torsoHeight / 2, -torsoHeight / 2, -torsoHeight / 2,
                 torsoHeight / 2, -torsoHeight / 2, torsoHeight / 2,
                 -torsoHeight / 2, -torsoHeight / 2, torsoHeight / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Simple3DCharacter::drawLimbsWithDetails() const
{
    glPushMatrix();

    drawLeftArm();
    drawRightArm();

    drawLeftLeg();
    drawRightLeg();

    glPopMatrix();
}

void Simple3DCharacter::drawLeftArm() const
{
    float xOffset = scale * 2.0f / 2.0f + 1.0f;
    float yOffset = scale * 1.0f + limbLength / 2.0f - 0.2f * limbLength;

    glPushMatrix();
    glTranslatef(0.0f, (limbLength / 2.0f), 0.0f);
    glRotatef(armLeftRotationAngle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -(limbLength / 2.0f), 0.0f);
    drawLimb(limbLength, limbWidth, xOffset, yOffset, 0.0f, 90.0f);
    glPopMatrix();
}

void Simple3DCharacter::drawRightArm() const
{
    float xOffset = -(scale * 2.0f / 2.0f + 1.0f);
    float yOffset = scale * 1.0f + limbLength / 2.0f - 0.2f * limbLength;

    glPushMatrix();
    glTranslatef(0.0f, (limbLength / 2.0f), 0.0f);
    glRotatef(armRightRotationAngle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -(limbLength / 2.0f), 0.0f);
    drawLimb(limbLength, limbWidth, xOffset, yOffset, 0.0f, 90.0f);
    glPopMatrix();
}

void Simple3DCharacter::drawLeftLeg() const
{
    glPushMatrix();
    glRotatef(legLeftRotationAngle, 1.0f, 0.0f, 0.0f);
    drawLimb(limbLength, limbWidth, scale * 2.0f / 2.0f, -(scale * 1.0f + limbLength / 2.0f), 0.0f, -90.0f);
    glPopMatrix();
}

void Simple3DCharacter::drawRightLeg() const
{
    glPushMatrix();
    glRotatef(legRightRotationAngle, 1.0f, 0.0f, 0.0f);
    drawLimb(limbLength, limbWidth, -scale * 2.0f / 2.0f, -(scale * 1.0f + limbLength / 2.0f), 0.0f, -90.0f);
    glPopMatrix();
}

void Simple3DCharacter::drawLimb(float length, float width, float xOffset, float yOffset, float zOffset, float rotationAngle) const
{
    glPushMatrix();
    glTranslatef(xOffset, yOffset, zOffset);

    glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCylinder(width, length, 10, 10);
    glPopMatrix();
}

void Simple3DCharacter::drawAdditionalComponents() const
{
    glPushMatrix();
    glTranslatef(0.0f, torsoHeight * 0.6f, 0.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    glScalef(1.5f, 0.3f, 1.0f);
    glutSolidCube(scale * 1.5f);
    glPopMatrix();
}

void Simple3DCharacter::startWalking() { isWalking = true; }

void Simple3DCharacter::stopWalking() { isWalking = false; }

void Simple3DCharacter::jump() { physics->jump(); }

void Simple3DCharacter::move(float deltaTime)
{
    bool isMoving = movement->updatePosition(posX, posZ, deltaTime, rotationAngleCharacter);

    if (isMoving)
    {
        startWalking();
    }
    else
    {
        stopWalking();
    }
}

void Simple3DCharacter::setMoveForward(bool value) { movement->setMoveForward(value); }
void Simple3DCharacter::setMoveBackward(bool value) { movement->setMoveBackward(value); }
void Simple3DCharacter::setMoveLeft(bool value) { movement->setMoveLeft(value); }
void Simple3DCharacter::setMoveRight(bool value) { movement->setMoveRight(value); }

void Simple3DCharacter::draw() const
{
    const float heightZero = limbLength / 2.0f + torsoHeight / 2.0f;
    glPushMatrix();

    glTranslatef(posX, posY + heightZero, posZ);
    glRotatef(rotationAngleCharacter, 0.0f, 1.0f, 0.0f);
    drawTorso();
    drawHead();
    drawLimbsWithDetails();
    drawAdditionalComponents();

    glPopMatrix();
}

void Simple3DCharacter::update(float deltaTime, const Terrain &terrain)
{
    physics->setCharacterPosition(posX, posZ, terrain);
    physics->applyPhysics(deltaTime, terrain);
    physics->handleCollision(deltaTime, terrain);
    posY = physics->getCharacterY();
    physics->update(deltaTime, terrain);

    move(deltaTime);

    if (isWalking)
    {
        animator->walkAnimation(deltaTime);
        return;
    }

    animator->idleAnimation(deltaTime);
}

float Simple3DCharacter::getPosX()
{
    return posX;
}

float Simple3DCharacter::getPosY()
{
    return posY;
}

float Simple3DCharacter::getPosZ()
{
    return posZ;
}

float Simple3DCharacter::getFootHeight() const
{
    float footHeight = (torsoHeight / 2.0f) - limbLength - 0.5f;

    return footHeight;
}
