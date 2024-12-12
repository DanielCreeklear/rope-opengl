#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glut.h>

class Light
{
public:
    Light();
    void initialize();
    void applyLighting();
    void moveLight(float dx, float dy, float dz);
    void adjustBrightness(float ambientFactor, float diffuseFactor);
    void drawLightIndicator();

private:
    float position[4];
    float ambientLight[4];
    float diffuseLight[4];
};

#endif
