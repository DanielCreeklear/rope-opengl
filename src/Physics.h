#ifndef PHYSICS_H
#define PHYSICS_H

class Terrain;

// Small deterministic point-mass model used by both the character and ball.
class Physics
{
public:
    Physics(float gravity, float damping, float jumpForce, float groundOffset = 0.0f);

    void reset(float x, float y, float z);
    void setPosition(float x, float y, float z);
    void setVelocity(float x, float y, float z);
    void setHorizontalPosition(float x, float z);
    void update(float deltaTime, const Terrain &terrain);
    void jump();

    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    float getVelocityX() const { return velocityX; }
    float getVelocityY() const { return velocityY; }
    float getVelocityZ() const { return velocityZ; }
    bool isOnGround() const { return onGround; }

private:
    float x, y, z;
    float velocityX, velocityY, velocityZ;
    float gravity, damping, jumpForce, groundOffset;
    bool onGround;
};

#endif
