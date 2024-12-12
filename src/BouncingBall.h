#ifndef BOUNCINGBALL_H
#define BOUNCINGBALL_H

#include <GL/glut.h>
// #include "Texture.h"

class Terrain;
class Physics;

class BouncingBall
{
private:
    float radius;
    float posX, posY, posZ;
    float velocityX, velocityY, velocityZ;
    Physics *physics;

    GLuint textureID;

    void setMaterial(const float ambient[4], const float diffuse[4], const float specular[4], float shininess) const;

public:
    BouncingBall(float radius, float initialPosX, float initialPosY, float initialPosZ);
    ~BouncingBall();

    void draw() const;
    void init();

    void update(float deltaTime, const Terrain &terrain);

    void setVelocity(float vx, float vy, float vz);
    void setPosition(float x, float y, float z);

    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getPosZ() const { return posZ; }
};

#endif