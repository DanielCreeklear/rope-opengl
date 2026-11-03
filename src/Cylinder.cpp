#include <GL/glut.h>
#include "Cylinder.h"
#include <memory>

void drawCylinder(float radius, float height, int slices, int stacks)
{
    static std::unique_ptr<GLUquadric, decltype(&gluDeleteQuadric)> quadric(gluNewQuadric(), &gluDeleteQuadric);
    if (!quadric) return;
    gluQuadricNormals(quadric.get(), GLU_SMOOTH);

    glColor3f(1.0f, 1.0f, 1.0f);
    gluQuadricOrientation(quadric.get(), GLU_INSIDE);
    glPushMatrix();
    gluDisk(quadric.get(), 0.0f, radius, slices, stacks);
    glPopMatrix();

    gluQuadricOrientation(quadric.get(), GLU_OUTSIDE);
    gluCylinder(quadric.get(), radius, radius, height, slices, stacks);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(quadric.get(), 0.0f, radius, slices, stacks);
    glPopMatrix();

}
