#include "BouncingBall.h"
#include "Physics.h"
#include "Terrain.h"

BouncingBall::BouncingBall(float radius, float initialPosX, float initialPosY, float initialPosZ)
    : radius(radius), posX(initialPosX), posY(initialPosY), posZ(initialPosZ), velocityX(0.0f), velocityY(0.0f), velocityZ(0.0f)
{
    physics = new Physics(-9.8f, 0.8f, initialPosY, 0.8f);
}

BouncingBall::~BouncingBall()
{
    delete physics;
}

void BouncingBall::draw() const
{
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glColor3f(0.0f, 0.5f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    float ambientHead[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float diffuseHead[4] = {0.8f, 0.8f, 0.8f, 1.0f};
    float specularHead[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    setMaterial(ambientHead, diffuseHead, specularHead, 32.0f);

    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    gluSphere(quadric, radius, 50, 50);
    glPopMatrix();
}

void BouncingBall::update(float deltaTime, const Terrain &terrain)
{
    physics->applyPhysics(deltaTime, terrain);
    physics->setCharacterPosition(posX, posZ, terrain);
    physics->handleCollision(deltaTime, terrain);
    posY = physics->getCharacterY() + radius + 0.5f;

    if (posY - radius <= terrain.getHeightAtPosition(posX, posZ))
    {
        physics->jump();
    }
}

void BouncingBall::setVelocity(float vx, float vy, float vz)
{
    velocityX = vx;
    velocityY = vy;
    velocityZ = vz;
}

void BouncingBall::setPosition(float x, float y, float z)
{
    posX = x;
    posY = y;
    posZ = z;
}

void BouncingBall::setMaterial(const float ambient[4], const float diffuse[4], const float specular[4], float shininess) const
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void BouncingBall::init()
{
    // loadTexture("src/bola.png", &textureID);
}