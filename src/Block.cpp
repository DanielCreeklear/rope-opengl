#include "Block.h"

Block::Block(float x, float y, float z, float size)
    : x(x), y(y), z(z), size(size) {}

void Block::draw() const
{
    glPushMatrix();
    glTranslatef(x, y, z);

    GLfloat materialAmbient[] = {color[0] * 0.3f, color[1] * 0.3f, color[2] * 0.3f, 1.0f};
    GLfloat materialDiffuse[] = {color[0], color[1], color[2], 1.0f};
    GLfloat materialSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat materialShininess = 32.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    glBegin(GL_QUADS);

    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);

    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);

    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);

    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);

    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);

    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(-size / 2, -size / 2, -size / 2);

    glEnd();
    glPopMatrix();
}

float Block::getX() const
{
    return x;
}

float Block::getY() const
{
    return y;
}

float Block::getZ() const
{
    return z;
}

void Block::setColor(float r, float g, float b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}
