#include <GL/freeglut.h>
#include "input.h"
#include "Globals.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

namespace
{
bool draggingBall = false;
double dragPlaneY = 0.0;
double dragOffsetX = 0.0;
double dragOffsetZ = 0.0;

bool rayForPixel(int mouseX, int mouseY, GLdouble &nearX, GLdouble &nearY, GLdouble &nearZ,
                 GLdouble &dirX, GLdouble &dirY, GLdouble &dirZ)
{
    int viewport[4];
    double modelview[16], projection[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    const double winX = static_cast<double>(mouseX);
    const double winY = static_cast<double>(viewport[3] - mouseY);
    GLdouble farX, farY, farZ;
    if (gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &nearX, &nearY, &nearZ) != GLU_TRUE ||
        gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &farX, &farY, &farZ) != GLU_TRUE)
        return false;
    dirX = farX - nearX; dirY = farY - nearY; dirZ = farZ - nearZ;
    return dirX * dirX + dirY * dirY + dirZ * dirZ > 1e-12;
}

bool rayPlaneY(int mouseX, int mouseY, double planeY, double &worldX, double &worldZ)
{
    GLdouble nearX, nearY, nearZ, dirX, dirY, dirZ;
    if (!rayForPixel(mouseX, mouseY, nearX, nearY, nearZ, dirX, dirY, dirZ) || std::abs(dirY) < 1e-9)
        return false;
    const double t = (planeY - nearY) / dirY;
    if (t < 0.0) return false;
    worldX = nearX + t * dirX;
    worldZ = nearZ + t * dirZ;
    return true;
}

void shutdownApplication()
{
    Globals::character.releaseGraphicsResources();
    Globals::ball.releaseGraphicsResources();
    glutLeaveMainLoop();
}
}

bool screenToWorld(int mouseX, int mouseY, GLdouble &worldX, GLdouble &worldY, GLdouble &worldZ)
{
    GLdouble nearX, nearY, nearZ, dirX, dirY, dirZ;
    if (!rayForPixel(mouseX, mouseY, nearX, nearY, nearZ, dirX, dirY, dirZ)) return false;

    const double cx = Globals::ball.getPosX();
    const double cy = Globals::ball.getPosY();
    const double cz = Globals::ball.getPosZ();
    const double radius = Globals::ball.getRadius();
    const double a = dirX * dirX + dirY * dirY + dirZ * dirZ;
    const double ox = nearX - cx, oy = nearY - cy, oz = nearZ - cz;
    const double b = 2.0 * (ox * dirX + oy * dirY + oz * dirZ);
    const double c = ox * ox + oy * oy + oz * oz - radius * radius;
    const double discriminant = b * b - 4.0 * a * c;
    if (a <= 1e-12 || discriminant < 0.0) return false;
    double t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (t < 0.0) t = (-b + std::sqrt(discriminant)) / (2.0 * a);
    if (t < 0.0) return false;
    worldX = nearX + t * dirX;
    worldY = nearY + t * dirY;
    worldZ = nearZ + t * dirZ;
    return true;
}

void mouseMotion(int x, int y)
{
    if (draggingBall)
    {
        double worldX, worldZ;
        if (rayPlaneY(x, y, dragPlaneY, worldX, worldZ))
            Globals::ball.setPosition(static_cast<float>(worldX + dragOffsetX), static_cast<float>(dragPlaneY), static_cast<float>(worldZ + dragOffsetZ));
    }
    Globals::camera.mouseMotion(x, y);
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            GLdouble hitX, hitY, hitZ;
            draggingBall = screenToWorld(x, y, hitX, hitY, hitZ);
            if (draggingBall)
            {
                const double centerX = Globals::ball.getPosX();
                dragPlaneY = Globals::ball.getPosY();
                const double centerZ = Globals::ball.getPosZ();
                double planeX, planeZ;
                if (!rayPlaneY(x, y, dragPlaneY, planeX, planeZ)) draggingBall = false;
                else
                {
                    dragOffsetX = centerX - planeX;
                    dragOffsetZ = centerZ - planeZ;
                    Globals::ball.setVelocity(0.0f, 0.0f, 0.0f);
                }
            }
        }
        else draggingBall = false;
    }

    Globals::camera.mouseButton(button, state, x, y);
}

void keyboardSpecial(int key, int, int)
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

void keyboard(unsigned char key, int, int)
{
    const float moveSpeed = 1.0f;

    switch (key)
    {
    case 'w':
        Globals::character.setIdle(false);
        Globals::character.setMoveForward(true);
        break;
    case 's':
        Globals::character.setIdle(false);
        Globals::character.setMoveBackward(true);
        break;
    case 'a':
        Globals::character.setIdle(false);
        Globals::character.setMoveLeft(true);
        break;
    case 'd':
        Globals::character.setIdle(false);
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
        shutdownApplication();
        break;
    default:
        break;
    }
}

void keyboardUp(unsigned char key, int, int)
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
    case ' ':
        break;
    default:
        break;
    }
    Globals::character.setIdle(!Globals::character.hasMovementInput());
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
        Globals::ball.restartPosition();
        break;
    case 6:
        shutdownApplication();
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
