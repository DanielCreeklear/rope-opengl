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

void keyboardSpecial(int key, int x, int y)
{
    const float lightMoveSpeed = 0.5f;
    switch (key)
    {
    case GLUT_KEY_UP:
        Globals::light.moveLight(0.0f, lightMoveSpeed, 0.0f);
        break;
    case GLUT_KEY_DOWN:
        Globals::light.moveLight(0.0f, -lightMoveSpeed, 0.0f);
        break;
    case GLUT_KEY_LEFT:
        Globals::light.moveLight(-lightMoveSpeed, 0.0f, 0.0f);
        break;
    case GLUT_KEY_RIGHT:
        Globals::light.moveLight(lightMoveSpeed, 0.0f, 0.0f);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    const float moveSpeed = 1.0f;

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
        Globals::character.setIdle(false);
        Globals::character.jump();
        break;
    case 'r':
        Globals::character.setIdle(false);
        Globals::character.increaseAngleLeftArm(moveSpeed);
        break;
    case 'f':
        Globals::character.setIdle(false);
        Globals::character.increaseAngleLeftArm(-moveSpeed);
        break;
    case 't':
        Globals::character.setIdle(false);
        Globals::character.increaseAngleRightArm(moveSpeed);
        break;
    case 'g':
        Globals::character.setIdle(false);
        Globals::character.increaseAngleRightArm(-moveSpeed);
        break;
    case '+':
        Globals::light.adjustBrightness(0.5f, 0.5f);
        break;
    case '-':
        Globals::light.adjustBrightness(-0.5f, -0.5f);
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
        Globals::character.setIdle(true);
        break;
    case 's':
        Globals::character.setMoveBackward(false);
        Globals::character.setIdle(true);
        break;
    case 'a':
        Globals::character.setMoveLeft(false);
        Globals::character.setIdle(true);
        break;
    case 'd':
        Globals::character.setMoveRight(false);
        Globals::character.setIdle(true);
        break;
    case ' ':
        Globals::character.setIdle(true);
        break;
    default:
        break;
    }
}

void menuHandler(int option)
{
    switch (option)
    {
    case 1:
        Globals::light.adjustBrightness(0.5f, 0.5f);
        break;
    case 2:
        Globals::light.adjustBrightness(-0.5f, -0.5f);
        break;
    case 3:
        Globals::character.startCelebration(true);
        break;
    case 4:
        Globals::character.startCelebration(false);
        break;
    case 5:
        Globals::character.resetCharacter();
        break;
    case 6:
        exit(0);
        break;
    default:
        break;
    }
}

void createMenu()
{
    glutCreateMenu(menuHandler);
    glutAddMenuEntry("Aumentar Luminosidade", 1);
    glutAddMenuEntry("Diminuir Luminosidade", 2);
    glutAddMenuEntry("Iniciar danca", 3);
    glutAddMenuEntry("Parar danca", 4);
    glutAddMenuEntry("Reiniciar", 5);
    glutAddMenuEntry("Sair", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}