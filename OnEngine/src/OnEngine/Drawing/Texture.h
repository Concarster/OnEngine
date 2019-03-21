#pragma once

#include<iostream>
#include<string>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <SOIL2.h>

namespace on
{

    class Texture
    {
    private:
        GLuint m_ID;
        int m_Width;
        int m_Height;
        unsigned int m_Type;

    public:

        Texture(const char* fileName, GLenum type);
        

        ~Texture();
       

        inline GLuint getID() const { return this->m_ID; }

        void Bind(const GLint textureUnit);
        
        void Unbind();

        void LoadFromFile(const char* fileName);
        
    };

}