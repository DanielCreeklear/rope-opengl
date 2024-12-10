#define STB_IMAGE_IMPLEMENTATION
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#include "Axes.h"
#include "Camera.h"
#include "Light.h"
#include "AnimatedFigure.h"
#include "Simple3DCharacter.h"
#include "Terrain.h"
#include "BouncingBall.h"
#include "DebugTexture.h"

Camera camera;
Light light;
Simple3DCharacter character(1.0f, 3.0f, 1.0f, 5.0f, 0.3f);
BouncingBall ball(1.0f, 5.0f, 20.0f, 5.0f);

DebugTexture debugTex;

float lastFrameTime = 0.0f;

const float cameraOffsetX = 0.0f;
const float cameraOffsetY = 10.0f;
const float cameraOffsetZ = 30.0f;

Terrain *mainTerrain;

Terrain *createTerrain(float height)
{
    float blockSize = 1.0f;
    Terrain *terrain = new Terrain(blockSize, 20, 20, height + blockSize);
    return terrain;
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    if (!debugTex.loadTexture("src/pelo.png"))
    {
        std::cerr << "Erro ao carregar a textura!" << std::endl;
        exit(1);
    }

    light.initialize();
    camera.setup();

    mainTerrain = createTerrain(0.0f);
    character.draw();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.applyViewTransform(character.getPosX(), character.getPosY(), character.getPosZ());
    light.applyLighting();

    mainTerrain->draw();
    drawAxes();
    character.draw();
    ball.draw();

    debugTex.renderTextureQuad();

    glutSwapBuffers();
}

void update(int value)
{
    float currentFrameTime = glutGet(GLUT_ELAPSED_TIME);

    float deltaTime = (currentFrameTime - lastFrameTime) * 0.001f;

    lastFrameTime = currentFrameTime;

    character.update(deltaTime, *mainTerrain);
    ball.update(deltaTime, *mainTerrain);

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
