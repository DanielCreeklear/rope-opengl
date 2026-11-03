#include "BouncingBall.h"
#include "Terrain.h"
#include <iostream>

BouncingBall::BouncingBall(float radius, float initialPosX, float initialPosY, float initialPosZ)
    : radius(radius), initialPosX(initialPosX), initialPosY(initialPosY), initialPosZ(initialPosZ),
      physics(-9.8f, 0.8f, 0.0f, radius), quadric(nullptr, &gluDeleteQuadric), textureID(0)
{
    physics.reset(initialPosX, initialPosY, initialPosZ);
}

BouncingBall::~BouncingBall()
{
    releaseGraphicsResources();
}

void BouncingBall::releaseGraphicsResources()
{
    if (textureID != 0) glDeleteTextures(1, &textureID);
    textureID = 0;
    quadric.reset();
}

void BouncingBall::draw() const
{
    glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
    glPushMatrix();
    glTranslatef(getPosX(), getPosY(), getPosZ());
    glColor3f(0.0f, 0.5f, 1.0f);
    if (textureID != 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    else glDisable(GL_TEXTURE_2D);

    const float ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    const float diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    const float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    setMaterial(ambient, diffuse, specular, 32.0f);
    if (quadric) gluSphere(quadric.get(), radius, 40, 32);
    glPopMatrix();
    glPopAttrib();
}

void BouncingBall::update(float deltaTime, const Terrain &terrain)
{
    physics.update(deltaTime, terrain);
}

void BouncingBall::setVelocity(float vx, float vy, float vz)
{
    physics.setVelocity(vx, vy, vz);
}

void BouncingBall::setPosition(float x, float y, float z)
{
    physics.reset(x, y, z);
}

void BouncingBall::setMaterial(const float ambient[4], const float diffuse[4], const float specular[4], float shininess) const
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void BouncingBall::init()
{
    if (!quadric) quadric.reset(gluNewQuadric());
    if (quadric)
    {
        gluQuadricTexture(quadric.get(), GL_TRUE);
        gluQuadricNormals(quadric.get(), GLU_SMOOTH);
    }
    loadTexture("src/bola.png", &textureID);
}

void BouncingBall::restartPosition()
{
    physics.reset(initialPosX, initialPosY, initialPosZ);
}
