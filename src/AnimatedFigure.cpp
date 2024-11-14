// AnimatedFigure.cpp
#include "AnimatedFigure.h"
#include <GL/glut.h>
#include <cmath>

AnimatedFigure::AnimatedFigure()
    : rotationAngle(0.0f)
{
}

void AnimatedFigure::draw()
{
    // Desenha o corpo (cilindro)
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 0.3f);
    glTranslatef(0.0f, -1.0f, 0.0f); // Move para baixo para o centro da base
    glScalef(0.5f, 1.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Desenha a cabeça (esfera) com rotação
    glPushMatrix();
    glColor3f(0.8f, 0.5f, 0.3f);
    glTranslatef(0.0f, 0.5f, 0.0f); // Coloca acima do "corpo"
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Aplica rotação
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    // Desenha os "braços" (dois cilindros, um de cada lado)
    glPushMatrix();
    glColor3f(0.2f, 0.5f, 0.9f);
    glTranslatef(-0.6f, 0.0f, 0.0f); // Lado esquerdo do corpo
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f); // Rotaciona para ficar na horizontal
    GLUquadric* quadric = gluNewQuadric();
    gluCylinder(quadric, 0.1f, 0.1f, 0.5f, 20, 20);
    gluDeleteQuadric(quadric);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2f, 0.5f, 0.9f);
    glTranslatef(0.6f, 0.0f, 0.0f); // Lado direito do corpo
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f); // Rotaciona para ficar na horizontal
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.1f, 0.1f, 0.5f, 20, 20);
    gluDeleteQuadric(quadric);
    glPopMatrix();
}

void AnimatedFigure::update(float delta)
{
    rotationAngle += 90.0f * delta; // Gira a cabeça a 90 graus por segundo
    if (rotationAngle > 360.0f)
        rotationAngle -= 360.0f; // Mantém o ângulo entre 0 e 360
}
