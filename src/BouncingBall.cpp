#include "BouncingBall.h"
#include "Physics.h"
#include "Terrain.h"

BouncingBall::BouncingBall(float radius, float initialPosX, float initialPosY, float initialPosZ)
    : radius(radius), posX(initialPosX), posY(initialPosY), posZ(initialPosZ), velocityX(0.0f), velocityY(0.0f), velocityZ(0.0f)
{
    physics = new Physics(-9.8f, 0.8f, initialPosY, 0.8f);
}

BouncingBall::~BouncingBall()
{
    delete physics;
}

void BouncingBall::draw() const
{
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glColor3f(0.0f, 0.5f, 1.0f);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
}

void BouncingBall::update(float deltaTime, const Terrain &terrain)
{
    physics->applyPhysics(deltaTime, terrain);
    physics->setCharacterPosition(posX, posZ, terrain);
    physics->handleCollision(deltaTime, terrain);
    posY = physics->getCharacterY() + radius + 0.5f;

    if (posY - radius <= terrain.getHeightAtPosition(posX, posZ))
    {
        physics->jump();
    }
}

void BouncingBall::setVelocity(float vx, float vy, float vz)
{
    velocityX = vx;
    velocityY = vy;
    velocityZ = vz;
}

void BouncingBall::setPosition(float x, float y, float z)
{
    posX = x;
    posY = y;
    posZ = z;
}