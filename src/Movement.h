#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement
{
public:
    Movement(float speed)
        : speed(speed), moveForward(false), moveBackward(false), moveLeft(false), moveRight(false) {}

    void setMoveForward(bool value) { moveForward = value; }
    void setMoveBackward(bool value) { moveBackward = value; }
    void setMoveLeft(bool value) { moveLeft = value; }
    void setMoveRight(bool value) { moveRight = value; }

    bool updatePosition(float &posX, float &posZ, float deltaTime, float &rotationAngle);

private:
    float speed;
    bool moveForward, moveBackward, moveLeft, moveRight;
};

#endif