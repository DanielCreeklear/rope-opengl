#include "Terrain.h"

Terrain::Terrain(float blockSize, int width, int depth, float height)
    : blockSize(blockSize), width(width), depth(depth), groundHeight(height)
{
    generateTerrain();
}

void Terrain::generateTerrain()
{
    for (int x = 0; x < width; ++x)
    {
        for (int z = 0; z < depth; ++z)
        {
            blocks.emplace_back(x * blockSize, groundHeight, z * blockSize, blockSize);
        }
    }
}

void Terrain::draw() const
{
    for (const Block &block : blocks)
    {
        block.draw();
    }
}

void Terrain::setHeight(float height)
{
    groundHeight = height;
}
