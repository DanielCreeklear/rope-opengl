#include "Simple3DCharacter.h"
#include "Cylinder.h"
#include <algorithm>

Simple3DCharacter::Simple3DCharacter(float scale, float torsoHeight, float headRadius, float limbLength, float limbWidth)
    : scale(scale), torsoHeight(torsoHeight), headRadius(headRadius), limbLength(limbLength), limbWidth(limbWidth),
      armLeftRotationAngle(0.0f), armRightRotationAngle(0.0f), legLeftRotationAngle(0.0f), legRightRotationAngle(0.0f),
      torsoRotationAngle(0.0f), headRotationAngle(0.0f), directionRightArmRotation(1.0f), directionLeftArmRotation(-1.0f), directionLeftLegRotation(1.0f),
      directionRightLegRotation(-1.0f), directionHeadRotation(1.0f), directionTorsoRotation(1.0f), isWalking(false),
      moveForward(false), moveBackward(false), moveLeft(false), moveRight(false), posX(0.0f), posY(0.0f), posZ(0.0f) {}

void Simple3DCharacter::draw() const
{
    glPushMatrix();

    glTranslatef(posX, posY, posZ);
    drawTorso();
    drawHead();
    drawLimbsWithDetails();
    drawAdditionalComponents();

    glPopMatrix();
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
    glutSolidCube(torsoHeight);
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

void Simple3DCharacter::rotateWithLimits(float &angle, float speed, float &direction, float minAngle, float maxAngle, float deltaTime)
{
    if (angle > maxAngle)
    {
        angle = maxAngle;
        direction = -1.0f;
    }
    else if (angle < minAngle)
    {
        angle = minAngle;
        direction = 1.0f;
    }

    angle += speed * direction;
}

void Simple3DCharacter::startWalking()
{
    isWalking = true;
}

void Simple3DCharacter::stopWalking()
{
    isWalking = false;
}

void Simple3DCharacter::walkAnimation(float deltaTime)
{
    const float velocity = 3.0f;
    const float armSpeed = 1.0f * velocity;
    const float legSpeed = 1.0f * velocity;
    const float headSpeed = 2.0f * velocity;

    const float armMaxAngle = 45.0f;
    const float armMinAngle = -45.0f;
    const float legMaxAngle = 30.0f;
    const float legMinAngle = -30.0f;
    const float headMaxAngle = 30.0f;
    const float headMinAngle = -30.0f;

    rotateWithLimits(armLeftRotationAngle, armSpeed, directionLeftArmRotation, armMinAngle, armMaxAngle, deltaTime);
    rotateWithLimits(armRightRotationAngle, armSpeed, directionRightArmRotation, armMinAngle, armMaxAngle, deltaTime);
    rotateWithLimits(legLeftRotationAngle, legSpeed, directionLeftLegRotation, legMinAngle, legMaxAngle, deltaTime);
    rotateWithLimits(legRightRotationAngle, legSpeed, directionRightLegRotation, legMinAngle, legMaxAngle, deltaTime);
    rotateWithLimits(headRotationAngle, headSpeed, directionHeadRotation, headMinAngle, headMaxAngle, deltaTime);
}

void Simple3DCharacter::idleAnimation(float deltaTime)
{
    float torsoOscillationSpeed = 0.08f;
    float torsoMaxAngle = 3.0f;
    float torsoMinAngle = -3.0f;
    rotateWithLimits(torsoRotationAngle, torsoOscillationSpeed, directionTorsoRotation, torsoMinAngle, torsoMaxAngle, deltaTime);

    float headOscillationSpeed = 0.1f;
    float headMaxAngle = 5.0f;
    float headMinAngle = -5.0f;
    rotateWithLimits(headRotationAngle, headOscillationSpeed, directionHeadRotation, headMinAngle, headMaxAngle, deltaTime);

    float armOscillationSpeed = 0.2f;
    float armMaxAngle = 5.0f;
    float armMinAngle = -5.0f;
    rotateWithLimits(armLeftRotationAngle, armOscillationSpeed, directionLeftArmRotation, armMinAngle, armMaxAngle, deltaTime);
    rotateWithLimits(armRightRotationAngle, armOscillationSpeed, directionRightArmRotation, armMinAngle, armMaxAngle, deltaTime);
}

void Simple3DCharacter::move(float deltaTime)
{
    const float moveSpeed = 0.1f;
    bool isMoving = false;

    if (moveForward)
    {
        posZ -= moveSpeed;
        isMoving = true;
    }
    if (moveBackward)
    {
        posZ += moveSpeed;
        isMoving = true;
    }
    if (moveLeft)
    {
        posX -= moveSpeed;
        isMoving = true;
    }
    if (moveRight)
    {
        posX += moveSpeed;
        isMoving = true;
    }

    if (isMoving)
    {
        startWalking();
    }
    else
    {
        stopWalking();
    }
}

void Simple3DCharacter::update(float deltaTime)
{
    move(deltaTime);

    if (isWalking)
    {
        walkAnimation(deltaTime);
        return;
    }

    idleAnimation(deltaTime);
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
