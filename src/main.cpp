#include <GL/freeglut.h>
#include <algorithm>
#include "Globals.h"
#include "input.h"
#include "Axes.h"

namespace
{
constexpr float fixedStep = 1.0f / 120.0f;
int previousTime = 0;
float accumulator = 0.0f;

void reshape(int width, int height)
{
    Globals::camera.reshape(width, height);
}

void closeWindow()
{
    Globals::character.releaseGraphicsResources();
    Globals::ball.releaseGraphicsResources();
}
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    Globals::light.initialize();
    Globals::camera.setup(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    Globals::ball.init();
    Globals::character.init();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Globals::camera.applyViewTransform(Globals::character.getPosX(), Globals::character.getPosY(), Globals::character.getPosZ());
    Globals::light.applyLighting();
    Globals::mainTerrain.draw();
    drawAxes();
    Globals::character.draw();
    Globals::ball.draw();
    Globals::light.drawLightIndicator();
    glutSwapBuffers();
}

void update(int)
{
    const int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float elapsed = static_cast<float>(currentTime - previousTime) * 0.001f;
    previousTime = currentTime;
    elapsed = std::min(elapsed, 0.1f); // avoid a large simulation jump after a pause
    accumulator += elapsed;
    while (accumulator >= fixedStep)
    {
        Globals::character.update(fixedStep, Globals::mainTerrain, Globals::ball);
        Globals::ball.update(fixedStep, Globals::mainTerrain);
        accumulator -= fixedStep;
    }
    glutPostRedisplay();
    glutTimerFunc(8, update, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rope OpenGL - Character and Ball Demo");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutCloseFunc(closeWindow);

    init();
    createMenu();
    glutPassiveMotionFunc(mouseMotion);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(keyboardSpecial);
    glutMouseWheelFunc([](int, int direction, int, int) { Globals::camera.mouseWheel(0, direction, 0, 0); });
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    previousTime = glutGet(GLUT_ELAPSED_TIME);
    glutTimerFunc(8, update, 0);
    glutMainLoop();
    return 0;
}
