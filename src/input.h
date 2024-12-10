#ifndef INPUT_H
#define INPUT_H

bool isMouseOverBall(int mouseX, int mouseY);
void mouseMotion(int x, int y);
void mouseButton(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

#endif