#ifndef INPUT_H
#define INPUT_H

#include <GL/glut.h>

void screenToWorld(int mouseX, int mouseY, GLdouble &worldX, GLdouble &worldY, GLdouble &worldZ);
void mouseMotion(int x, int y);
void mouseButton(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

#endif