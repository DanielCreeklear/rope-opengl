#include "Terrain.h"
#include <cmath>

Terrain::Terrain(float blockSize, int width, int depth, float height)
    : blockSize(blockSize), groundHeight(height), width(width), depth(depth)
{
    generateTerrain();
}

void Terrain::generateTerrain()
{
    blocks.clear();
    blocks.reserve(static_cast<std::size_t>(width * depth));
    for (int x = 0; x < width; ++x)
    {
        for (int z = 0; z < depth; ++z)
        {
            Block block((x + 0.5f) * blockSize, groundHeight, (z + 0.5f) * blockSize, blockSize);

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

float Terrain::getHeightAtPosition(float x, float z) const
{
    const int blockX = static_cast<int>(std::floor(x / blockSize));
    const int blockZ = static_cast<int>(std::floor(z / blockSize));

    if (blockX >= 0 && blockX < width && blockZ >= 0 && blockZ < depth)
    {
        return blocks[blockX * depth + blockZ].getY() + blockSize * 0.5f;
    }
    return groundHeight + blockSize * 0.5f;
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
    generateTerrain();
}

bool Terrain::isWithinTerrain(float x, float z) const
{
    return x >= 0.0f && x < width * blockSize && z >= 0.0f && z < depth * blockSize;
}
