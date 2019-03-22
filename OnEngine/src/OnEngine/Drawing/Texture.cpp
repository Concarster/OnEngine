#include "OnPCH.h"
#include "Texture.h"

namespace on
{

    Texture::Texture(const char * fileName, GLenum type)
    {
        this->m_Type = type;

        unsigned char* image = SOIL_load_image(fileName, &this->m_Width, &this->m_Height, NULL, SOIL_LOAD_RGBA);

        glGenTextures(1, &this->m_ID);
        glBindTexture(type, this->m_ID);

        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (image)
        {
            glTexImage2D(type, 0, GL_RGBA, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(type);
        }
        else
        {
            ON_ENGINE_ERROR("ERROR::TEXTURE::TEXTURE_LOADING_FAILED: {0}", fileName);
        }

        glActiveTexture(0);
        glBindTexture(type, 0);
        SOIL_free_image_data(image);
    }



    Texture::~Texture()
    {
        glDeleteTextures(1, &this->m_ID);
    }

    void Texture::Bind(const GLint textureUnit)
    {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(this->m_Type, this->m_ID);
    }

    void Texture::Unbind()
    {
        glActiveTexture(0);
        glBindTexture(this->m_Type, 0);
    }

    void Texture::LoadFromFile(const char * fileName)
    {
        if (this->m_ID)
        {
            glDeleteTextures(1, &this->m_ID);
        }

        unsigned char* image = SOIL_load_image(fileName, &this->m_Width, &this->m_Height, NULL, SOIL_LOAD_RGBA);

        glGenTextures(1, &this->m_ID);
        glBindTexture(this->m_Type, this->m_ID);

        glTexParameteri(this->m_Type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(this->m_Type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(this->m_Type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(this->m_Type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (image)
        {
            glTexImage2D(this->m_Type, 0, GL_RGBA, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(this->m_Type);
        }
        else
        {
            ON_ENGINE_ERROR("ERROR::TEXTURE::TEXTURE_LOADING_FAILED: {0}", fileName);
        }

        glActiveTexture(0);
        glBindTexture(this->m_Type, 0);
        SOIL_free_image_data(image);
    }

}