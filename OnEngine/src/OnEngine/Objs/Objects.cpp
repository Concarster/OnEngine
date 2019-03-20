#include "OnPCH.h"
#include "Objects.h"

namespace on
{

    Objects::Objects()
       /* :m_Size(200),
        m_Width(900),
        m_Height(600)*/
    {
    }


    Objects::~Objects()
    {
    }

    LoadShaders Objects::GetShader()
    {
        //return on::LoadShaders();
        return m_Shader;
    }

    GLuint Objects::GetProgramId()
    {
        //return GLuint();
        return m_ProgramID;
    }

    GLuint Objects::GetVAO()
    {
        //return GLuint();
        return m_VAO;
    }

    GLuint Objects::GetVBO()
    {
        //return GLuint();
        return m_VBO;
    }

    GLuint Objects::GetEBO()
    {
        //return GLuint();
        return m_EBO;
    }

}