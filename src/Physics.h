#ifndef PHYSICS_H
#define PHYSICS_H

#include <cmath>

class Terrain;

class Physics
{
public:
    Physics(float gravity, float damping, float groundY, float jumpForce)
        : gravity(gravity), damping(damping), groundY(groundY), jumpForce(jumpForce),
          velocityY(0.0f), isJumping(false), onGround(false), characterY(groundY) {}

    void applyPhysics(float deltaTime, const Terrain &terrain);
    void handleCollision(float deltaTime, const Terrain &terrain);
    void update(float deltaTime, const Terrain &terrain);
    void jump();

    float getCharacterY() const { return characterY; }
    void setCharacterPosition(float x, float z, const Terrain &terrain);

private:
    bool isJumping;
    bool onGround;
    float velocityY;
    float gravity;
    float damping;
    float groundY;
    float jumpForce;
    float characterX, characterY, characterZ;
};

#endif