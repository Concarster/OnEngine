#include "OnPCH.h"
#include "ImageMgr.h"
#include <SOIL2.h>

namespace on
{

    ImageMgr::ImageMgr()
    {
    }


    ImageMgr::~ImageMgr()
    {
    }

    void ImageMgr::Init()
    {

    }

    void ImageMgr::LoadTexture(const char* filePath)
    {
        m_Image = SOIL_load_image(filePath, &m_ImageWith, &m_ImageHeight, NULL, SOIL_LOAD_RGBA);
        //m_Image = SOIL_load_image("Assets/Textures/sun.png", &m_ImageWith, &m_ImageHeight, NULL, SOIL_LOAD_AUTO);
    }

    void ImageMgr::LoadTexture(const char* filePath, int width, int height)
    {
        m_Image = SOIL_load_image(filePath, &width, &height, NULL, SOIL_LOAD_RGBA);
    }

    void ImageMgr::GenerateTexture()
    {
        int width = 0;
        int height = 0;

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        if (m_Image)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            ON_ENGINE_ERROR("ERROR::TEXTURE_LOADING_FAILED");
        }

        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        SOIL_free_image_data(m_Image);
    }

    void ImageMgr::GenerateTexture(GLuint & textureID)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    void ImageMgr::GenTexture(unsigned char * LoadTexture(const char *filePath))
    {
    }

    void ImageMgr::GenTexture(const char * filePath)
    {
        m_Image = SOIL_load_image(filePath, &m_ImageWith, &m_ImageHeight, NULL, SOIL_LOAD_RGBA);

        int width = 0;
        int height = 0;

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (m_Image)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            ON_ENGINE_ERROR("ERROR::TEXTURE_LOADING_FAILED");
        }

        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        SOIL_free_image_data(m_Image);

    }

    void ImageMgr::GenTexture(const char * filePath, GLuint & texture)
    {
        int width = 0;
        int height = 0;

        m_Image = SOIL_load_image(filePath, &width, &height, NULL, SOIL_LOAD_RGBA);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (m_Image)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            ON_ENGINE_ERROR("ERROR::TEXTURE_LOADING_FAILED");
        }

        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        SOIL_free_image_data(m_Image);
    }

    

   

}