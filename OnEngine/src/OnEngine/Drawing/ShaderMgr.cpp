#include "OnPCH.h"
#include "ShaderMgr.h"

namespace on
{
    ShaderMgr::ShaderMgr(const int versionMajor, const int versionMinor, char * vertexFile, char * fragmentFile, char * geometryFile)
        : m_VersionMajor(versionMajor), 
          m_VersionMinor(versionMinor)
    {
        GLuint vertexShader = 0;
        GLuint geometryShader = 0;
        GLuint fragmentShader = 0;

        vertexShader = LoadShader(GL_VERTEX_SHADER, vertexFile);

        if (geometryFile != "")
            geometryShader = LoadShader(GL_GEOMETRY_SHADER, geometryFile);

        fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentFile);

        this->LinkShader(vertexShader, geometryShader, fragmentShader);

        //End
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);
    }

    ShaderMgr::~ShaderMgr()
    {
        glDeleteProgram(this->m_ID);
    }

    void ShaderMgr::SetUniform1i(GLint value, const GLchar * name)
    {
        this->Use();

        glUniform1i(glGetUniformLocation(this->m_ID, name), value);

        this->UnUse();
    }

    void ShaderMgr::SetUniform1f(GLfloat value, const GLchar * name)
    {
        this->Use();

        glUniform1f(glGetUniformLocation(this->m_ID, name), value);

        this->UnUse();
    }

    void ShaderMgr::SetVec2f(glm::fvec2 value, const GLchar * name)
    {
        this->Use();

        glUniform2fv(glGetUniformLocation(this->m_ID, name), 1, glm::value_ptr(value));

        this->UnUse();
    }

    void ShaderMgr::SetVec3f(glm::fvec3 value, const GLchar * name)
    {
        this->Use();

        glUniform3fv(glGetUniformLocation(this->m_ID, name), 1, glm::value_ptr(value));

        this->UnUse();
    }

    void ShaderMgr::SetVec4f(glm::fvec4 value, const GLchar * name)
    {
        this->Use();

        glUniform4fv(glGetUniformLocation(this->m_ID, name), 1, glm::value_ptr(value));

        this->UnUse();
    }

    void ShaderMgr::SetMat3fv(glm::mat3 value, const GLchar * name, GLboolean transpose)
    {
        this->Use();

        glUniformMatrix3fv(glGetUniformLocation(this->m_ID, name), 1, transpose, glm::value_ptr(value));

        this->UnUse();
    }

    void ShaderMgr::SetMat4fv(glm::mat4 value, const GLchar * name, GLboolean transpose)
    {
        this->Use();

        glUniformMatrix4fv(glGetUniformLocation(this->m_ID, name), 1, transpose, glm::value_ptr(value));

        this->UnUse();
    }

    std::string ShaderMgr::LoadShaderSrc(char * fileName)
    {
        std::string temp = "";
        std::string src = "";

        std::ifstream in_file;

        //Vertex
        in_file.open(fileName);

        if (in_file.is_open())
        {
            while (std::getline(in_file, temp))
                src += temp + "\n";
        }
        else
        {
            ON_ENGINE_ERROR("ERROR::SHADER::COULD_NOT_OPEN_FILE: {0}", fileName);
        }

        in_file.close();

        std::string versionNumber = std::to_string(this->m_VersionMajor) + std::to_string(this->m_VersionMinor) + "0";

        src.replace(src.find("#version"), 12, ("#version " + versionNumber));

        return src;
    }

    GLuint ShaderMgr::LoadShader(GLenum type, char * fileName)
    {
        char infoLog[512];
        GLint success;

        GLuint shader = glCreateShader(type);

        std::string str_src = this->LoadShaderSrc(fileName);

        const GLchar* src = str_src.c_str();

        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);

            ON_ENGINE_ERROR("ERROR::SHADER::COULD_NOT_COMPILE_SHADER: {0} \n {1} \n", fileName, infoLog);
           
        }

        return shader;
    }

    void ShaderMgr::LinkShader(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
    {
        char infoLog[512];
        GLint success;

        this->m_ID = glCreateProgram();

        glAttachShader(this->m_ID, vertexShader);

        if (geometryShader)
            glAttachShader(this->m_ID, geometryShader);

        glAttachShader(this->m_ID, fragmentShader);

        glLinkProgram(this->m_ID);

        glGetProgramiv(this->m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->m_ID, 512, NULL, infoLog);
            ON_ENGINE_ERROR("ERROR::SHADER::COULD_NOT_LINK_PROGRAM {0} \n", infoLog);
           
        }

        glUseProgram(0);
    }

    void ShaderMgr::CheckCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
               
                ON_ENGINE_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: {0} \n {1} \n", type, infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                
                ON_ENGINE_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {0} \n {1} \n", type, infoLog);
            }
        }
    }

}