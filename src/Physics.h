#ifndef PHYSICS_H
#define PHYSICS_H

#include <cmath>

class Physics
{
public:
    Physics(float gravity, float damping, float groundY, float jumpForce)
        : gravity(gravity), damping(damping), groundY(groundY), jumpForce(jumpForce),
          velocityY(0.0f), isJumping(false), onGround(true), characterY(groundY) {}

    void applyPhysics(float deltaTime);
    void handleCollision(float deltaTime);
    void jump();
    void update(float deltaTime);

    float getCharacterY() const { return characterY; }

private:
    bool isJumping;
    bool onGround;
    float velocityY;
    float gravity;
    float damping;
    float groundY;
    float jumpForce;
    float characterY;
};

#endif