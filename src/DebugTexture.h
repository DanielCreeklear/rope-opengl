#include <GL/glut.h>
#include <iostream>
#include "stb_image.h"

class DebugTexture
{
public:
    GLuint textureID;

    DebugTexture() : textureID(0) {}

    bool loadTexture(const char *textureFile)
    {
        int width, height, channels;
        unsigned char *data = stbi_load(textureFile, &width, &height, &channels, STBI_rgb_alpha);

        if (!data)
        {
            std::cerr << "Erro ao carregar a textura: " << textureFile << std::endl;
            return false;
        }

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);

        return true;
    }

    void renderTextureQuad()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, -5.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 5.0f, 0.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 5.0f, 0.0f);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

    ~DebugTexture()
    {
        if (textureID)
        {
            glDeleteTextures(1, &textureID);
        }
    }
};
