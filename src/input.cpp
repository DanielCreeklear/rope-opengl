#include "input.h"
#include "Globals.h"


void mouseMotion(int x, int y)
{
    Globals::camera.mouseMotion(x, y);
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == 3)
    {
        if (state == GLUT_DOWN)
        {
            Globals::isButtonPressed = true;
        }
        else if (state == GLUT_UP)
        {
            Globals::isButtonPressed = false;
        }
    }

    x = x;
    y = y;
    Globals::camera.mouseButton(button, state, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
    const float moveSpeed = 0.1f;

    switch (key)
    {
    case 'w':
        Globals::character.setMoveForward(true);
        break;
    case 's':
        Globals::character.setMoveBackward(true);
        break;
    case 'a':
        Globals::character.setMoveLeft(true);
        break;
    case 'd':
        Globals::character.setMoveRight(true);
        break;
    case ' ':
        Globals::character.jump();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void keyboardUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        Globals::character.setMoveForward(false);
        break;
    case 's':
        Globals::character.setMoveBackward(false);
        break;
    case 'a':
        Globals::character.setMoveLeft(false);
        break;
    case 'd':
        Globals::character.setMoveRight(false);
        break;
    default:
        break;
    }
}