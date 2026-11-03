#include "Movement.h"
#include "Physics.h"
#include "Terrain.h"
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cmath>

int main()
{
    constexpr float step = 1.0f / 120.0f;
    Terrain terrain(1.0f, 4, 3, 1.0f);
    assert(terrain.isWithinTerrain(0.1f, 0.1f));
    assert(!terrain.isWithinTerrain(4.0f, 0.1f));
    assert(std::abs(terrain.getHeightAtPosition(2.2f, 1.1f) - 1.5f) < 1e-6f);

    Physics first(-9.8f, 0.8f, 0.0f, 0.5f);
    Physics second(-9.8f, 0.8f, 0.0f, 0.5f);
    first.reset(1.0f, 5.0f, 1.0f);
    second.reset(1.0f, 5.0f, 1.0f);
    for (int i = 0; i < 20000 && (!first.isOnGround() || !second.isOnGround()); ++i)
    {
        first.update(step, terrain);
        second.update(step, terrain);
    }
    assert(std::abs(first.getX() - second.getX()) < 1e-6f);
    assert(std::abs(first.getY() - second.getY()) < 1e-6f);
    assert(first.getY() >= 2.0f);
    assert(first.isOnGround());

    Movement movement(10.0f);
    movement.setMoveForward(true);
    movement.setMoveRight(true);
    float x = 0.0f, z = 0.0f, angle = 0.0f;
    assert(movement.updatePosition(x, z, 1.0f, angle));
    assert(std::abs(std::sqrt(x * x + z * z) - 10.0f) < 1e-5f);
    assert(std::abs(x - std::sqrt(50.0f)) < 1e-5f);
    assert(std::abs(z + std::sqrt(50.0f)) < 1e-5f);

    movement.setMoveRight(false);
    movement.setMoveBackward(true);
    assert(!movement.updatePosition(x, z, 1.0f, angle)); // opposite keys cancel
    return 0;
}
