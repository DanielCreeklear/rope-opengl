#include "Physics.h"
#include "Terrain.h"

void Physics::applyPhysics(float deltaTime, const Terrain &terrain)
{
    if (!terrain.isWithinTerrain(characterX, characterZ))
    {
        onGround = false;
        velocityY += gravity * deltaTime;
        characterY += velocityY * deltaTime;
    }
    else
    {
        if (!onGround)
        {
            velocityY += gravity * deltaTime;
            characterY += velocityY * deltaTime;

            float terrainHeight = terrain.getHeightAtPosition(characterX, characterZ);

            if (characterY <= terrainHeight)
            {
                characterY = terrainHeight;
                velocityY = 0.0f;
                isJumping = false;
                onGround = true;
            }
        }
    }
}

void Physics::handleCollision(float deltaTime, const Terrain &terrain)
{
    if (!terrain.isWithinTerrain(characterX, characterZ))
    {
        onGround = false;
        return;
    }

    float terrainHeight = terrain.getHeightAtPosition(characterX, characterZ);

    if (characterY <= terrainHeight)
    {
        characterY = terrainHeight;

        if (std::abs(velocityY) > 0.5f)
        {
            velocityY = -velocityY * damping;
        }
        else
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

void Physics::update(float deltaTime, const Terrain &terrain)
{
    if (!terrain.isWithinTerrain(characterX, characterZ))
    {
        onGround = false;
        velocityY += gravity * deltaTime;
        characterY += velocityY * deltaTime;
        return;
    }

    float terrainHeight = terrain.getHeightAtPosition(characterX, characterZ);

    if (characterY <= terrainHeight)
    {
        characterY = terrainHeight;
        velocityY = -velocityY * damping;

        if (std::abs(velocityY) < 0.1f)
        {
            velocityY = 0.0f;
        }
    }
}

void Physics::setCharacterPosition(float x, float z, const Terrain &terrain)
{
    characterX = x;
    characterZ = z;

    if (!terrain.isWithinTerrain(characterX, characterZ))
    {
        onGround = false;
    }
}
