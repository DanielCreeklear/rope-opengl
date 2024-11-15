#ifndef BLOCK_H
#define BLOCK_H

#include <GL/glut.h>

class Block
{
public:
    Block(float x, float y, float z, float size);
    void draw() const;

    float getX() const;
    float getY() const;
    float getZ() const;

private:
    float x, y, z;
    float size;
};

#endif
