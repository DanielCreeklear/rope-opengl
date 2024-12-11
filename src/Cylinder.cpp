#include <GL/glut.h>
#include "Cylinder.h"

void drawCylinder(float radius, float height, int slices, int stacks)
{
    GLUquadric *quadric = gluNewQuadric();

    glColor3b(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    gluDisk(quadric, 0.0f, radius, slices, stacks);
    glPopMatrix();

    gluCylinder(quadric, radius, radius, height, slices, stacks);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(quadric, 0.0f, radius, slices, stacks);
    glPopMatrix();

    gluDeleteQuadric(quadric);
}
