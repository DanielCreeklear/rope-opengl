#include <GL/glut.h>
#include <cmath>
#include "Axes.h"
#include "Camera.h"
#include "Light.h"
#include "AnimatedFigure.h"
#include "Simple3DCharacter.h"
#include <GL/freeglut_ext.h>

Camera camera;
Light light;
Simple3DCharacter character(1.0f, 3.0f, 1.0f, 5.0f, 0.3f);

float time = 0.0f;

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    light.initialize();
    camera.setup();
    camera.setPosition(0.0f, 0.0f, 5.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.applyViewTransform();
    light.applyLighting();

    drawAxes();
    character.draw();

    glutSwapBuffers();
}

void update(int value)
{
    time += 0.05f;
    character.update(time);
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void mouseMotion(int x, int y)
{
    camera.mouseMotion(x, y);
}

void mouseButton(int button, int state, int x, int y)
{
    camera.mouseButton(button, state, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
    const float moveSpeed = 1.0f;

    switch (key)
    {
    case 'w':
        camera.moveForward(moveSpeed);
        break;
    case 's':
        camera.moveBackward(moveSpeed);
        break;
    case 'a':
        camera.moveLeft(moveSpeed);
        break;
    case 'd':
        camera.moveRight(moveSpeed);
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rope OpenGL");

    init();

    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton);
    glutKeyboardFunc(keyboard);

    glutMouseWheelFunc([](int button, int direction, int x, int y)
                       { camera.mouseWheel(button, direction, x, y); });

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
