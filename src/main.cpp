#define STB_IMAGE_IMPLEMENTATION
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#include "Globals.h"
#include "input.h"
#include "Axes.h"
#include "Terrain.h"
#include "DebugTexture.h"


DebugTexture debugTex;

float lastFrameTime = 0.0f;

const float cameraOffsetX = 0.0f;
const float cameraOffsetY = 10.0f;
const float cameraOffsetZ = 30.0f;


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

    Globals::light.initialize();
    Globals::camera.setup();

    Globals::mainTerrain = createTerrain(0.0f);
    Globals::character.draw();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Globals::camera.applyViewTransform(Globals::character.getPosX(), Globals::character.getPosY(), Globals::character.getPosZ());
    Globals::light.applyLighting();

    Globals::mainTerrain->draw();
    drawAxes();
    Globals::character.draw();
    Globals::ball.draw();

    debugTex.renderTextureQuad();

    glutSwapBuffers();
}

void update(int value)
{
    float currentFrameTime = glutGet(GLUT_ELAPSED_TIME);

    float deltaTime = (currentFrameTime - lastFrameTime) * 0.001f;

    lastFrameTime = currentFrameTime;

    Globals::character.update(deltaTime, *Globals::mainTerrain);
    Globals::ball.update(deltaTime, *Globals::mainTerrain);

    if (Globals::isButtonPressed)
    {
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

        float mouseX = (float)(Globals::x - windowWidth / 2) / (windowWidth / 2);
        float mouseZ = -(float)(Globals::y - windowHeight / 2) / (windowHeight / 2);

        Globals::ball.setPosition(mouseX, Globals::ball.getPosY(), mouseZ);
    }

    glutPostRedisplay();

    glutTimerFunc(16, update, 0);
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
                       { Globals::camera.mouseWheel(button, direction, x, y); });

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
