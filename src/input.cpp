#include "input.h"
#include "Globals.h"
#include <iostream>

const float BALL_DETECTION_RADIUS = 50.0f;

void screenToWorld(int mouseX, int mouseY, GLdouble &worldX, GLdouble &worldY, GLdouble &worldZ)
{
    int viewport[4];
    double modelview[16];
    double projection[16];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    float winX = (float)mouseX;
    float winY = (float)(viewport[3] - mouseY);

    float fixedPlaneY = Globals::ball.getPosY();

    GLdouble nearX, nearY, nearZ;
    GLdouble farX, farY, farZ;

    gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &nearX, &nearY, &nearZ);
    gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &farX, &farY, &farZ);

    double dirX = farX - nearX;
    double dirY = farY - nearY;
    double dirZ = farZ - nearZ;

    double length = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
    dirX /= length;
    dirY /= length;
    dirZ /= length;

    if (dirY != 0.0)
    {
        double t = (fixedPlaneY - nearY) / dirY;
        worldX = nearX + t * dirX;
        worldY = fixedPlaneY;
        worldZ = nearZ + t * dirZ;
    }
    else
    {
        worldX = nearX;
        worldY = fixedPlaneY;
        worldZ = nearZ;
    }
}

void mouseMotion(int x, int y)
{
    Globals::x = x;
    Globals::y = y;
    Globals::camera.mouseMotion(x, y);
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == 1)
    {
        if (state == GLUT_DOWN)
        {
            Globals::isButtonPressed = !Globals::isButtonPressed;
            
        }
    }

    Globals::x = x;
    Globals::y = y;
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