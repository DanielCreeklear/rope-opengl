#ifndef GLOBALS_H
#define GLOBALS_H

#include "Camera.h"
#include "Simple3DCharacter.h"
#include "Terrain.h"
#include "Light.h"
#include "BouncingBall.h"

namespace Globals
{
    extern Camera camera;
    extern Light light;
    extern Simple3DCharacter character;
    extern BouncingBall ball;
    extern Terrain *mainTerrain;
    extern bool isButtonPressed;
    extern int x, y;
}

#endif
