#include "Animator.h"

Animator::Animator(Simple3DCharacter *character)
{
    this->character = character;
}

void Animator::rotateWithLimits(float &angle, float speed, float &direction, float minAngle, float maxAngle, float deltaTime)
{
    if (angle > maxAngle)
    {
        angle = maxAngle;
        direction = -1.0f;
    }
    else if (angle < minAngle)
    {
        angle = minAngle;
        direction = 1.0f;
    }

    angle += speed * direction * deltaTime;
}

void Animator::walkAnimation(float deltaTime)
{
    const float velocity = 300.0f;
    const float armSpeed = 1.0f * velocity;
    const float legSpeed = 1.0f * velocity;
    const float headSpeed = 2.0f * velocity;

    const float armMaxAngle = 45.0f;
    const float armMinAngle = -45.0f;
    const float legMaxAngle = 30.0f;
    const float legMinAngle = -30.0f;
    const float headMaxAngle = 30.0f;
    const float headMinAngle = -30.0f;

    rotateWithLimits(character->armLeftRotationAngle, armSpeed, character->directionLeftArmRotation, armMinAngle, armMaxAngle, deltaTime);
    rotateWithLimits(character->armRightRotationAngle, armSpeed, character->directionRightArmRotation, armMinAngle, armMaxAngle, deltaTime);
    rotateWithLimits(character->legLeftRotationAngle, legSpeed, character->directionLeftLegRotation, legMinAngle, legMaxAngle, deltaTime);
    rotateWithLimits(character->legRightRotationAngle, legSpeed, character->directionRightLegRotation, legMinAngle, legMaxAngle, deltaTime);
    rotateWithLimits(character->headRotationAngle, headSpeed, character->directionHeadRotation, headMinAngle, headMaxAngle, deltaTime);
}

void Animator::idleAnimation(float deltaTime)
{
    const float velocity = 50.0f;
    float torsoOscillationSpeed = 0.08f * velocity;
    float torsoMaxAngle = 3.0f;
    float torsoMinAngle = -3.0f;
    rotateWithLimits(character->torsoRotationAngle, torsoOscillationSpeed, character->directionTorsoRotation, torsoMinAngle, torsoMaxAngle, deltaTime);

    float headOscillationSpeed = 0.1f * velocity;
    float headMaxAngle = 5.0f;
    float headMinAngle = -5.0f;
    rotateWithLimits(character->headRotationAngle, headOscillationSpeed, character->directionHeadRotation, headMinAngle, headMaxAngle, deltaTime);

    float armOscillationSpeed = 0.2f * velocity;
    float armMaxAngle = 5.0f;
    float armMinAngle = -5.0f;
    rotateWithLimits(character->armLeftRotationAngle, armOscillationSpeed, character->directionLeftArmRotation, armMinAngle, armMaxAngle, deltaTime);
    rotateWithLimits(character->armRightRotationAngle, armOscillationSpeed, character->directionRightArmRotation, armMinAngle, armMaxAngle, deltaTime);
}
