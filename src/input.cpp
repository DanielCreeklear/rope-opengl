#include "input.h"
#include "Globals.h"

const float BALL_DETECTION_RADIUS = 50.0f;

bool isMouseOverBall(int mouseX, int mouseY)
{
    int viewport[4];
    double modelview[16];
    double projection[16];
    GLdouble ballScreenX, ballScreenY, ballScreenZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    float ballX = Globals::ball.getPosX();
    float ballY = Globals::ball.getPosY();
    float ballZ = Globals::ball.getPosZ();

    gluProject(ballX, ballY, ballZ, modelview, projection, viewport, &ballScreenX, &ballScreenY, &ballScreenZ);

    ballScreenY = viewport[3] - ballScreenY;

    float dx = mouseX - ballScreenX;
    float dy = mouseY - ballScreenY;
    float distance = sqrt(dx * dx + dy * dy);

    return distance <= BALL_DETECTION_RADIUS;
}

void mouseMotion(int x, int y)
{
    Globals::camera.mouseMotion(x, y);
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == 1)
    {
        if (state == GLUT_DOWN && isMouseOverBall(x, y))
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