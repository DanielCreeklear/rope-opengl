#ifndef BOUNCINGBALL_H
#define BOUNCINGBALL_H

#include <GL/glut.h>

class Terrain;
class Physics;

class BouncingBall
{
private:
    float radius;
    float posX, posY, posZ;
    float velocityX, velocityY, velocityZ;
    Physics *physics;

public:
    BouncingBall(float radius, float initialPosX, float initialPosY, float initialPosZ);
    ~BouncingBall();

    void draw() const;

    void update(float deltaTime, const Terrain &terrain);

    void setVelocity(float vx, float vy, float vz);

    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getPosZ() const { return posZ; }
};

#endif