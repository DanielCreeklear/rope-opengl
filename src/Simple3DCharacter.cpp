#include "Simple3DCharacter.h"
#include "Cylinder.h"
#include "Animator.h"
#include "Physics.h"
#include "Movement.h"
#include "Terrain.h"
#include "SolidCube.h"
#include "BouncingBall.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>

Simple3DCharacter::Simple3DCharacter(float scale, float torsoHeight, float headRadius, float limbLength, float limbWidth)
    : rotationAngleCharacter(0.0f), armRightRotationAngle(0.0f), armLeftRotationAngle(0.0f),
      directionRightArmRotation(1.0f), directionLeftArmRotation(-1.0f), directionTorsoRotation(1.0f),
      legLeftRotationAngle(0.0f), legRightRotationAngle(0.0f), directionLeftLegRotation(1.0f),
      directionRightLegRotation(-1.0f), torsoRotationAngle(0.0f), headRotationAngle(0.0f), directionHeadRotation(1.0f),
      scale(scale), torsoHeight(torsoHeight), headRadius(headRadius), limbLength(limbLength), limbWidth(limbWidth),
      physics(-16.8f, 0.8f, 10.0f, -1.0f), isWalking(false), enableIdle(true), celebration(false), ballContact(false),
      textureIDTorso(0), textureIDHead(0), headQuadric(nullptr, &gluDeleteQuadric)
{
    animator = std::make_unique<Animator>(this);
    movement = std::make_unique<Movement>(10.0f);
    physics.reset(0.0f, 10.0f, 0.0f);
}

Simple3DCharacter::~Simple3DCharacter()
{
    releaseGraphicsResources();
}

void Simple3DCharacter::releaseGraphicsResources()
{
    const GLuint textures[] = {textureIDTorso, textureIDHead};
    if (textureIDTorso != 0 || textureIDHead != 0) glDeleteTextures(2, textures);
    textureIDTorso = textureIDHead = 0;
    headQuadric.reset();
}

void Simple3DCharacter::init()
{
    loadTexture("src/torso2.png", &textureIDTorso);
    loadTexture("src/head.png", &textureIDHead);
    headQuadric.reset(gluNewQuadric());
    if (headQuadric)
    {
        gluQuadricTexture(headQuadric.get(), GL_TRUE);
        gluQuadricNormals(headQuadric.get(), GLU_SMOOTH);
    }
}

void Simple3DCharacter::setMaterial(const float ambient[4], const float diffuse[4], const float specular[4], float shininess) const
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void Simple3DCharacter::drawHead() const
{
    glPushMatrix();

    glTranslatef(0.0f, torsoHeight + headRadius, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDHead);

    float ambientHead[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float diffuseHead[4] = {0.8f, 0.8f, 0.8f, 1.0f};
    float specularHead[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    setMaterial(ambientHead, diffuseHead, specularHead, 32.0f);

    glPushMatrix();
    glRotatef(50.0f, 1.0f, 0.0f, 0.0f);
    if (headQuadric)
    {
        gluSphere(headQuadric.get(), headRadius, 40, 32);
    }
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 0.0f, 0.0f);
    float ambientCone[4] = {0.3f, 0.1f, 0.1f, 1.0f};
    float diffuseCone[4] = {0.7f, 0.0f, 0.0f, 1.0f};
    float specularCone[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    setMaterial(ambientCone, diffuseCone, specularCone, 16.0f);

    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, headRadius);

    glutSolidCone(0.5f, headRadius * 1.5f, 10, 10);
    glPopMatrix();

    glPopMatrix();
}

void Simple3DCharacter::drawTorso() const
{
    const float ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    const float diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    const float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const float shininess = 32.0f;

    setMaterial(ambient, diffuse, specular, shininess);

    glPushMatrix();
    glTranslatef(0.0f, torsoHeight / 2.0f, 0.0f);
    glRotatef(torsoRotationAngle, 0.0f, 1.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);

    if (textureIDTorso)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureIDTorso);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }

    const float halfHeight = torsoHeight / 2.0f;

    const float vertices[8][3] = {
        {-halfHeight, -halfHeight, -halfHeight},
        {halfHeight, -halfHeight, -halfHeight},
        {halfHeight, halfHeight, -halfHeight},
        {-halfHeight, halfHeight, -halfHeight},
        {-halfHeight, -halfHeight, halfHeight},
        {halfHeight, -halfHeight, halfHeight},
        {halfHeight, halfHeight, halfHeight},
        {-halfHeight, halfHeight, halfHeight}};

    const int faces[6][4] = {
        {4, 5, 6, 7},
        {3, 2, 1, 0},
        {0, 4, 7, 3},
        {2, 6, 5, 1},
        {7, 6, 2, 3},
        {0, 1, 5, 4}};

    const float normals[6][3] = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, -1.0f},
        {-1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, -1.0f, 0.0f}};

    const float texCoords[6][4][2] = {
        {{0.0f, 0.5f}, {1.0f, 0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.5f}, {1.0f, 0.5f}}, // Face frente
        {{0.0f, 0.5f}, {1.0f, 0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.0f, 0.5f}, {1.0f, 0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.0f, 0.5f}, {1.0f, 0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.0f, 0.5f}, {1.0f, 0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f}},
    };

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; ++i)
    {
        glNormal3fv(normals[i]);
        for (int j = 0; j < 4; ++j)
        {
            glTexCoord2fv(texCoords[i][j]);
            glVertex3fv(vertices[faces[i][j]]);
        }
    }
    glEnd();

    if (textureIDTorso)
    {
        glDisable(GL_TEXTURE_2D);
    }

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
    float forearmRotationAngle = armLeftRotationAngle < 0.0f ? fabs(armLeftRotationAngle) * 2.0f : 0.0f;

    glPushMatrix();
    glTranslatef(0.0f, (limbLength / 2.0f), 0.0f);
    glRotatef(armLeftRotationAngle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -(limbLength / 2.0f), 0.0f);

    drawLimb(limbLength, limbWidth, xOffset, yOffset, 0.0f, 90.0f);

    glTranslatef(xOffset, (-1.0f * yOffset) / 2.0f, 0.0f);
    drawForearm(limbLength, limbWidth, forearmRotationAngle + 90.0f);
    glPopMatrix();
}

void Simple3DCharacter::drawRightArm() const
{
    float xOffset = -(scale * 2.0f / 2.0f + 1.0f);
    float yOffset = scale * 1.0f + limbLength / 2.0f - 0.2f * limbLength;
    float forearmRotationAngle = armRightRotationAngle < 0.0f ? fabs(armRightRotationAngle) * 2.0f : 0.0f;

    glPushMatrix();
    glTranslatef(0.0f, (limbLength / 2.0f), 0.0f);
    glRotatef(armRightRotationAngle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -(limbLength / 2.0f), 0.0f);

    drawLimb(limbLength, limbWidth, xOffset, yOffset, 0.0f, 90.0f);

    glTranslatef(xOffset, (-1.0f * yOffset) / 2.0f, 0.0f);
    drawForearm(limbLength, limbWidth, forearmRotationAngle + 90.0f);
    glPopMatrix();
}

void Simple3DCharacter::drawForearm(float length, float width, float rotationAngle) const
{
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);

    glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
    drawCylinder(width, length, 10, 10);

    glPopMatrix();
}

void Simple3DCharacter::drawCalf(float length, float width, float rotationAngle) const
{
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);

    glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
    drawCylinder(width, length, 10, 10);

    glPopMatrix();
}

void Simple3DCharacter::drawLeftLeg() const
{
    float xOffset = scale * 2.0f / 2.0f;
    float yOffset = -(scale * 1.0f + limbLength / 2.0f);
    float zOffset = 0.0f;
    float forearmRotationAngle = legLeftRotationAngle > 0.0f ? legLeftRotationAngle * -2.0f : 0.0f;

    glPushMatrix();
    glRotatef(legLeftRotationAngle, 1.0f, 0.0f, 0.0f);
    drawLimb(limbLength, limbWidth, xOffset, yOffset, zOffset, -90.0f);

    glTranslatef(xOffset, (1.0f * yOffset), zOffset);
    drawCalf(limbLength, limbWidth, 90.0f + forearmRotationAngle);

    glPopMatrix();
}

void Simple3DCharacter::drawRightLeg() const
{
    float xOffset = -scale * 2.0f / 2.0f;
    float yOffset = -(scale * 1.0f + limbLength / 2.0f);
    float zOffset = 0.0f;
    float forearmRotationAngle = legRightRotationAngle > 0.0f ? legRightRotationAngle * -2.0f : 0.0f;

    glPushMatrix();
    glRotatef(legRightRotationAngle, 1.0f, 0.0f, 0.0f);
    drawLimb(limbLength, limbWidth, xOffset, yOffset, zOffset, -90.0f);

    glTranslatef(xOffset, (1.0f * yOffset), zOffset);
    drawCalf(limbLength, limbWidth, 90.0f + forearmRotationAngle);

    glPopMatrix();
}

void Simple3DCharacter::drawLimb(float length, float width, float xOffset, float yOffset, float zOffset, float rotationAngle) const
{
    const float ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    const float diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
    const float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const float shininess = 32.0f;

    setMaterial(ambient, diffuse, specular, shininess);

    glPushMatrix();
    glTranslatef(xOffset, yOffset, zOffset);

    glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
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

void Simple3DCharacter::jump() { physics.jump(); }

void Simple3DCharacter::move(float deltaTime)
{
    float x = physics.getX();
    float z = physics.getZ();
    bool isMoving = movement->updatePosition(x, z, deltaTime, rotationAngleCharacter);
    physics.setHorizontalPosition(x, z);

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
bool Simple3DCharacter::hasMovementInput() const { return movement->isMoving(); }

void Simple3DCharacter::draw() const
{
    const float heightZero = limbLength / 2.0f + torsoHeight / 2.0f;
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_TEXTURE_BIT | GL_LIGHTING_BIT);
    glPushMatrix();

    glTranslatef(physics.getX(), physics.getY() + heightZero + limbLength, physics.getZ());
    glRotatef(rotationAngleCharacter, 0.0f, 1.0f, 0.0f);
    drawTorso();
    drawHead();
    drawLimbsWithDetails();
    drawAdditionalComponents();

    glPopMatrix();
    glPopAttrib();
}

void Simple3DCharacter::update(float deltaTime, const Terrain &terrain, BouncingBall &ball)
{
    physics.update(deltaTime, terrain);

    const bool touchingBall = checkCollisionWithBall(ball);
    if (touchingBall && !ballContact)
    {
        kickBall(ball);
    }
    ballContact = touchingBall;

    if (celebration)
    {
        animator->celebrationAnimation(deltaTime);
        return;
    }

    move(deltaTime);

    if (isWalking)
    {
        animator->walkAnimation(deltaTime);
        return;
    }

    if (enableIdle)
    {
        animator->idleAnimation(deltaTime);
    }
}

float Simple3DCharacter::getPosX() const
{
    return physics.getX();
}

float Simple3DCharacter::getPosY() const
{
    return physics.getY();
}

float Simple3DCharacter::getPosZ() const
{
    return physics.getZ();
}

float Simple3DCharacter::getFootHeight() const
{
    float footHeight = (torsoHeight / 2.0f) - limbLength - 0.5f;

    return footHeight;
}

void Simple3DCharacter::increaseAngleLeftArm(float angle)
{
    if (angle + armLeftRotationAngle < 90.0f && angle + armLeftRotationAngle > -90.0f)
    {
        armLeftRotationAngle += angle;
    }
}

void Simple3DCharacter::increaseAngleRightArm(float angle)
{
    if (angle + armRightRotationAngle < 90.0f && angle + armRightRotationAngle > -90.0f)
    {
        armRightRotationAngle += angle;
    }
}

void Simple3DCharacter::increaseAngleLeftLeg(float angle)
{
    if (angle + legLeftRotationAngle < 90.0f && angle + legLeftRotationAngle > -90.0f)
    {
        legLeftRotationAngle += angle;
    }
}

void Simple3DCharacter::increaseAngleRightLeg(float angle)
{
    if (angle + legRightRotationAngle < 90.0f && angle + legRightRotationAngle > -90.0f)
    {
        legRightRotationAngle += angle;
    }
}

void Simple3DCharacter::setIdle(bool state)
{
    enableIdle = state;
}

void Simple3DCharacter::startCelebration(bool state)
{
    celebration = state;
}

void Simple3DCharacter::resetCharacter()
{
    armLeftRotationAngle = 0.0f;
    armRightRotationAngle = 0.0f;
    legLeftRotationAngle = 0.0f;
    legRightRotationAngle = 0.0f;
    torsoRotationAngle = 0.0f;
    headRotationAngle = 0.0f;
    directionRightArmRotation = 1.0f;
    directionLeftArmRotation = -1.0f;
    directionLeftLegRotation = 1.0f;
    directionRightLegRotation = -1.0f;
    directionHeadRotation = 1.0f;
    directionTorsoRotation = 1.0f;
    isWalking = false;
    movement->setMoveForward(false);
    movement->setMoveBackward(false);
    movement->setMoveLeft(false);
    movement->setMoveRight(false);
    physics.reset(0.0f, 10.0f, 0.0f);
    rotationAngleCharacter = 0.0f;
    enableIdle = true;
    celebration = false;
    ballContact = false;
}

void Simple3DCharacter::kickBall(BouncingBall &ball)
{
    float kickForce = 20.0f;
    float kickAngle = rotationAngleCharacter + 90.0f;

    constexpr float pi = 3.14159265358979323846f;
    float directionX = cos(kickAngle * pi / 180.0f);
    float directionZ = sin(kickAngle * pi / 180.0f);

    ball.setVelocity(kickForce * directionX, 5.0f, kickForce * directionZ);
}

bool Simple3DCharacter::checkCollisionWithBall(BouncingBall &ball)
{
    // Approximate the character by a vertical capsule and test the sphere
    // against its axis segment, including vertical separation.
    const float characterRadius = std::max(0.45f, limbWidth * 1.5f);
    const float segmentBottom = physics.getY() + 0.25f;
    const float segmentTop = physics.getY() + torsoHeight + limbLength;
    const float closestY = std::max(segmentBottom, std::min(ball.getPosY(), segmentTop));
    const float dx = physics.getX() - ball.getPosX();
    const float dy = closestY - ball.getPosY();
    const float dz = physics.getZ() - ball.getPosZ();
    const float combinedRadius = ball.getRadius() + characterRadius;
    return dx * dx + dy * dy + dz * dz <= combinedRadius * combinedRadius;
}

float Simple3DCharacter::calculateRadius() const
{
    return std::max(headRadius, limbWidth * 1.5f);
}
