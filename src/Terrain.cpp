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
            Block block(x * blockSize, groundHeight, z * blockSize, blockSize);

            if ((x + z) % 2 == 0)
            {
                block.setColor(1.0f, 1.0f, 1.0f);
            }
            else
            {
                block.setColor(0.0f, 0.0f, 0.0f);
            }

            blocks.push_back(block);
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
