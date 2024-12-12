#ifndef TEXTURE_H
#define TEXTURE

#include <GL/glut.h>
#include <iostream>
#include "stb_image.h"

void loadTexture(const char *filename, GLuint *textureID);

#endif