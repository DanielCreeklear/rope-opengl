#include "Simple3DCharacter.h"
#include "Cylinder.h"
#include <algorithm>

Simple3DCharacter::Simple3DCharacter(float scale, float torsoHeight, float headRadius, float limbLength, float limbWidth)
    : scale(scale), torsoHeight(torsoHeight), headRadius(headRadius), limbLength(limbLength), limbWidth(limbWidth),
      armRotationAngle(0.0f), legRotationAngle(0.0f), headRotationAngle(0.0f) {}

void Simple3DCharacter::draw() const
{
    glPushMatrix();
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
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(torsoHeight);
    glPopMatrix();
}

void Simple3DCharacter::drawLimbsWithDetails() const
{
    glPushMatrix();

    glPushMatrix();
    glRotatef(armRotationAngle, 0.0f, 1.0f, 0.0f);
    drawLimb(limbLength, limbWidth, scale * 2.0f / 2.0f + 1.0f, scale * 1.0f + limbLength / 2.0f, 0.0f, 90.0f);
    drawLimb(limbLength, limbWidth, -(scale * 2.0f / 2.0f + 1.0f), scale * 1.0f + limbLength / 2.0f, 0.0f, 90.0f);
    glPopMatrix();

    glPushMatrix();
    glRotatef(legRotationAngle, 0.0f, 1.0f, 0.0f);
    drawLimb(limbLength, limbWidth, scale * 2.0f / 2.0f, -(scale * 1.0f + limbLength / 2.0f), 0.0f, -90.0f);
    drawLimb(limbLength, limbWidth, -scale * 2.0f / 2.0f, -(scale * 1.0f + limbLength / 2.0f), 0.0f, -90.0f);
    glPopMatrix();

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

void Simple3DCharacter::rotateWithLimits(float &angle, float &speed, float minAngle, float maxAngle, float deltaTime)
{
    // Atualiza o ângulo com base na velocidade e no tempo
    angle += speed * deltaTime;

    // Checa se o ângulo ultrapassou o limite superior
    if (angle > maxAngle)
    {
        angle = maxAngle;
        speed = -fabs(speed);
    }
    // Checa se o ângulo ultrapassou o limite inferior
    else if (angle < minAngle)
    {
        angle = minAngle;
        speed = fabs(speed);
    }
}

void Simple3DCharacter::update(float deltaTime)
{
    // Velocidade de rotação (ajustar conforme necessário)
    float armSpeed = 10.0f;
    float legSpeed = 5.0f;
    float headSpeed = 2.0f;

    // Limites para as rotações
    float armMaxAngle = 45.0f;
    float armMinAngle = -45.0f;
    float legMaxAngle = 30.0f;
    float legMinAngle = -30.0f;
    float headMaxAngle = 30.0f;
    float headMinAngle = -30.0f;

    // Atualiza os ângulos de rotação com limites
    rotateWithLimits(armRotationAngle, armSpeed, armMinAngle, armMaxAngle, deltaTime);
    rotateWithLimits(legRotationAngle, legSpeed, legMinAngle, legMaxAngle, deltaTime);
    rotateWithLimits(headRotationAngle, headSpeed, headMinAngle, headMaxAngle, deltaTime);
}
