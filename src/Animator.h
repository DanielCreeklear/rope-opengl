#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Simple3DCharacter.h"

class Animator
{
public:
    Animator(Simple3DCharacter *character);

    void rotateWithLimits(float &angle, float speed, float &direction, float minAngle, float maxAngle, float deltaTime);
    void walkAnimation(float deltaTime);
    void idleAnimation(float deltaTime);
    void celebrationAnimation(float deltaTime);

private:
    Simple3DCharacter *character;
};

#endif
