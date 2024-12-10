#include "Globals.h"

Camera Globals::camera;
Light Globals::light;
Simple3DCharacter Globals::character(1.0f, 3.0f, 1.0f, 3.0f, 0.3f);
BouncingBall Globals::ball(1.0f, 5.0f, 20.0f, 5.0f);
Terrain *Globals::mainTerrain = nullptr;
bool Globals::isButtonPressed = false;
int Globals::x = 0, Globals::y = 0;
