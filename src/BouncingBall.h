#ifndef BOUNCINGBALL_H
#define BOUNCINGBALL_H

#include <GL/glut.h>
#include <memory>
#include "Texture.h"
#include "Physics.h"

class Terrain;
class Physics;

class BouncingBall
{
private:
    float radius;
    float initialPosX, initialPosY, initialPosZ;
    Physics physics;
    std::unique_ptr<GLUquadric, decltype(&gluDeleteQuadric)> quadric;

    GLuint textureID;

    void setMaterial(const float ambient[4], const float diffuse[4], const float specular[4], float shininess) const;

public:
    BouncingBall(float radius, float initialPosX, float initialPosY, float initialPosZ);
    ~BouncingBall();
    BouncingBall(const BouncingBall &) = delete;
    BouncingBall &operator=(const BouncingBall &) = delete;

    void draw() const;
    void init();
    void releaseGraphicsResources();

    void update(float deltaTime, const Terrain &terrain);

    void setVelocity(float vx, float vy, float vz);
    void setPosition(float x, float y, float z);

    float getPosX() const { return physics.getX(); }
    float getPosY() const { return physics.getY(); }
    float getPosZ() const { return physics.getZ(); }

    float getRadius() const { return radius; }

    void restartPosition();
};

#endif
