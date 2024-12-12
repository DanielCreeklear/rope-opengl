#include "Light.h"

Light::Light()
{
    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 10.0f;
    position[3] = 1.0f;

    ambientLight[0] = ambientLight[1] = ambientLight[2] = 0.8f;
    ambientLight[3] = 1.0f;

    diffuseLight[0] = diffuseLight[1] = diffuseLight[2] = 0.8f;
    diffuseLight[3] = 1.0f;
}

void Light::initialize()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void Light::applyLighting()
{
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
}

void Light::moveLight(float dx, float dy, float dz)
{
    position[0] += dx;
    position[1] += dy;
    position[2] += dz;
}

void Light::adjustBrightness(float ambientFactor, float diffuseFactor)
{
    for (int i = 0; i < 3; ++i)
    {
        ambientLight[i] += ambientFactor;
        diffuseLight[i] += diffuseFactor;
    }
}

void Light::drawLightIndicator()
{
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);

    glColor3f(1.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    glPopAttrib();
}
