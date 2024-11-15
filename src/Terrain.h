#ifndef TERRAIN_H
#define TERRAIN_H

#include "Block.h"
#include <vector>

class Terrain
{
public:
    Terrain(float blockSize, int width, int depth, float height);
    void draw() const;
    void setHeight(float height);

private: 
    float blockSize,
    groundHeight;
    int width, depth;
    std::vector<Block> blocks;

    void generateTerrain();
};

#endif
