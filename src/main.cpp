#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#include "Axes.h"
#include "Camera.h"
#include "Light.h"
#include "AnimatedFigure.h"
#include "Simple3DCharacter.h"
#include "Terrain.h"

Camera camera;
Light light;
Simple3DCharacter character(1.0f, 3.0f, 1.0f, 5.0f, 0.3f);

float lastFrameTime = 0.0f;
float time = 0.0f;

const float cameraOffsetX = 0.0f;
const float cameraOffsetY = 10.0f;
const float cameraOffsetZ = 30.0f;

void createTerrain(float height)
{
    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, -10.0f);
    Terrain terrain(1.0f, 20, 20, height);
    terrain.draw();
    glPopMatrix();
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    light.initialize();
    camera.setup();
    // camera.setPosition(0.0f, 0.0f, 5.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.applyViewTransform(character.getPosX(), character.getPosY(), character.getPosZ());
    light.applyLighting();

    createTerrain(character.getFootHeight());
    drawAxes();
    character.draw();

    glutSwapBuffers();
}

void update(int value)
{
    float currentFrameTime = glutGet(GLUT_ELAPSED_TIME);

    float deltaTime = (currentFrameTime - lastFrameTime) * 0.001f;

    lastFrameTime = currentFrameTime;

    character.update(deltaTime);

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
    const float moveSpeed = 0.1f;

    switch (key)
    {
    case 'w':
        character.setMoveForward(true);
        break;
    case 's':
        character.setMoveBackward(true);
        break;
    case 'a':
        character.setMoveLeft(true);
        break;
    case 'd':
        character.setMoveRight(true);
        break;
    case ' ':
        character.jump();
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
        character.setMoveForward(false);
        break;
    case 's':
        character.setMoveBackward(false);
        break;
    case 'a':
        character.setMoveLeft(false);
        break;
    case 'd':
        character.setMoveRight(false);
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
    glutKeyboardUpFunc(keyboardUp);

    glutMouseWheelFunc([](int button, int direction, int x, int y)
                       { camera.mouseWheel(button, direction, x, y); });

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
