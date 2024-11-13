#include <GL/glut.h>
#include "Camera.h"
#include "Light.h"

Camera camera;
Light light;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    light.initialize();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    camera.setPosition(0.0f, 0.0f, 5.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.applyViewTransform();
    light.applyLighting();

    glutSwapBuffers();
}

void update(int value) {
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

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
