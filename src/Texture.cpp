#include "Texture.h"

void loadTexture(const char *filename, GLuint *textureID)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);

    if (!data)
    {
        std::cerr << "Erro ao carregar a textura: " << stbi_failure_reason() << std::endl;
        return;
    }

    std::cout << "Textura carregada com sucesso. Dimensões: " << width << "x" << height << std::endl;

    glGenTextures(1, textureID);
    if (textureID == 0)
    {
        stbi_image_free(data);
        return;
    }

    glBindTexture(GL_TEXTURE_2D, *textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}