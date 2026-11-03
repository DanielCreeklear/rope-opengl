#include "Texture.h"

bool loadTexture(const char *filename, GLuint *textureID)
{
    if (textureID == nullptr) return false;
    *textureID = 0;
    stbi_set_flip_vertically_on_load(1);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);

    if (!data)
    {
        std::cerr << "Erro ao carregar a textura: " << stbi_failure_reason() << std::endl;
        return false;
    }

    GLint previousBinding = 0;
    GLint previousAlignment = 4;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &previousBinding);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousAlignment);
    glGenTextures(1, textureID);
    if (*textureID == 0)
    {
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(previousBinding));
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, *textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glPixelStorei(GL_UNPACK_ALIGNMENT, previousAlignment);
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(previousBinding));
    return true;
}
