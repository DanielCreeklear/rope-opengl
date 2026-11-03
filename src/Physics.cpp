#include "Physics.h"
#include "Terrain.h"
#include <algorithm>
#include <cmath>

Physics::Physics(float gravity, float damping, float jumpForce, float groundOffset)
    : x(0.0f), y(0.0f), z(0.0f), velocityX(0.0f), velocityY(0.0f), velocityZ(0.0f),
      gravity(gravity), damping(std::max(0.0f, std::min(damping, 1.0f))),
      jumpForce(jumpForce), groundOffset(groundOffset), onGround(false)
{
}

void Physics::reset(float newX, float newY, float newZ)
{
    x = newX; y = newY; z = newZ;
    velocityX = velocityY = velocityZ = 0.0f;
    onGround = false;
}

void Physics::setPosition(float newX, float newY, float newZ)
{
    x = newX; y = newY; z = newZ;
}

void Physics::setVelocity(float vx, float vy, float vz)
{
    velocityX = vx; velocityY = vy; velocityZ = vz;
    onGround = false;
}

void Physics::setHorizontalPosition(float newX, float newZ)
{
    x = newX; z = newZ;
}

void Physics::update(float deltaTime, const Terrain &terrain)
{
    if (deltaTime <= 0.0f) return;

    x += velocityX * deltaTime;
    z += velocityZ * deltaTime;

    // Exponential damping makes the result independent of the update rate.
    const float horizontalDamping = std::exp(-1.2f * deltaTime);
    velocityX *= horizontalDamping;
    velocityZ *= horizontalDamping;

    const float previousY = y;
    const float previousVelocityY = velocityY;
    const float nextY = previousY + previousVelocityY * deltaTime + 0.5f * gravity * deltaTime * deltaTime;
    const float nextVelocityY = previousVelocityY + gravity * deltaTime;

    if (!terrain.isWithinTerrain(x, z))
    {
        y = nextY;
        velocityY = nextVelocityY;
        onGround = false;
        return;
    }

    const float floorY = terrain.getHeightAtPosition(x, z) + groundOffset;
    float impactTime = -1.0f;
    if (previousY <= floorY && previousVelocityY <= 0.0f)
    {
        impactTime = 0.0f;
    }
    else if (nextY <= floorY && nextVelocityY < 0.0f)
    {
        const float discriminant = previousVelocityY * previousVelocityY - 2.0f * gravity * (previousY - floorY);
        if (discriminant >= 0.0f)
            impactTime = (-previousVelocityY - std::sqrt(discriminant)) / gravity;
    }

    if (impactTime >= 0.0f && impactTime <= deltaTime)
    {
        const float impactVelocity = previousVelocityY + gravity * impactTime;
        const float remainingTime = deltaTime - impactTime;
        if (impactVelocity < -0.15f)
        {
            // Resolve the impact at its actual time inside the step, then
            // integrate the remaining part of the step after the bounce.
            velocityY = -impactVelocity * damping;
            y = floorY + velocityY * remainingTime + 0.5f * gravity * remainingTime * remainingTime;
            velocityY += gravity * remainingTime;
            if (y <= floorY && velocityY < 0.0f)
            {
                y = floorY;
                velocityY = 0.0f;
                onGround = true;
            }
            else onGround = false;
        }
        else
        {
            y = floorY;
            velocityY = 0.0f;
            onGround = true;
        }
    }
    else
    {
        y = nextY;
        velocityY = nextVelocityY;
        onGround = false;
    }
}

void Physics::jump()
{
    if (onGround)
    {
        velocityY = jumpForce;
        onGround = false;
    }
}
