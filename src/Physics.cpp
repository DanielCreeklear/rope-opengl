#include "Physics.h"

void Physics::applyPhysics(float deltaTime)
{
    if (!onGround)
    {
        velocityY += gravity * deltaTime;
        characterY += velocityY * deltaTime;

        if (characterY <= groundY)
        {
            characterY = groundY;
            velocityY = 0.0f;
            isJumping = false;
            onGround = true;
        }
    }
}

void Physics::handleCollision(float deltaTime)
{
    if (characterY <= groundY)
    {
        characterY = groundY;
        velocityY = -velocityY * damping;

        if (std::abs(velocityY) < 0.5f)
        {
            velocityY = 0.0f;
            isJumping = false;
        }

        onGround = true;
    }
    else
    {
        onGround = false;
    }
}

void Physics::jump()
{
    if (!isJumping && onGround)
    {
        velocityY = jumpForce;
        isJumping = true;
        onGround = false;
    }
}

void Physics::update(float deltaTime)
{
    if (characterY <= groundY)
    {
        characterY = groundY;
        velocityY = -velocityY * damping * deltaTime;

        if (std::abs(velocityY) < 0.1f)
            velocityY = 0.0f;
    }
}