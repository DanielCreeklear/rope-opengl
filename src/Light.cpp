#include "Light.h"
#include <GL/glut.h>

Light::Light()
{
    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 10.0f;
    position[3] = 1.0f;
}

void Light::initialize()
{
    GLfloat ambientLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void Light::applyLighting()
{
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}
