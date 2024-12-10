#include "Simple3DCharacter.h"
#include "Cylinder.h"
#include "Animator.h"
#include "Physics.h"
#include "Movement.h"
#include "Terrain.h"
#include "SolidCube.h"
#include <algorithm>
#include <cmath>
#include <iostream>

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
}

void Simple3DCharacter::init()
{
    loadTexture("src/pelo.png", &textureIDTorso);
}

void Simple3DCharacter::loadTexture(const char *filename, GLuint *textureID)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);

    if (!data)
    {
        std::cerr << "Erro ao carregar a textura: " << stbi_failure_reason() << std::endl;
        return;
    }

    std::cout << "Textura carregada com sucesso. Dimensões: " << width << "x" << height << std::endl;

    glGenTextures(1, textureID);
    if (textureID == 0)
    {
        std::cerr << "Erro ao gerar o Texture ID!" << std::endl;
        stbi_image_free(data);
        return;
    }

    glBindTexture(GL_TEXTURE_2D, *textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    std::cout << "Texture ID " << *textureID << " carregado e vinculado com sucesso." << std::endl;
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
        {0, 1, 2, 3},
        {0, 4, 7, 3},
        {1, 5, 6, 2},
        {3, 2, 6, 7},
        {0, 1, 5, 4}};

    const float normals[6][3] = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, -1.0f},
        {-1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, -1.0f, 0.0f}};

    const float texCoords[6][4][2] = {
        {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}},
        {{1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}},
        {{1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}}};

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
    float forearmRotationAngle = armLeftRotationAngle < 0.0f ? fabs(armRightRotationAngle) * 2.0f : 0.0f;

    glPushMatrix();
    glTranslatef(0.0f, (limbLength / 2.0f), 0.0f);
    glRotatef(armLeftRotationAngle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -(limbLength / 2.0f), 0.0f);

    drawLimb(limbLength, limbWidth, xOffset, yOffset, 0.0f, 90.0f);

    glTranslatef(xOffset, -1.0f * yOffset, 0.0f);
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

    glTranslatef(xOffset, -1.0f * yOffset, 0.0f);
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
    glColor3f(0.7f, 0.7f, 0.7f);

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

    glTranslatef(posX, posY + heightZero + limbLength, posZ);
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
