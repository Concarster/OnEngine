#pragma once
#include<iostream>
#include<fstream>
#include<string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace on
{

    class ShaderMgr
    {
    private:
        //Member variables
        GLuint m_ID;
        const int m_VersionMajor;
        const int m_VersionMinor;

    public:
        ShaderMgr(const int versionMajor, const int versionMinor, char* vertexFile, char* fragmentFile, char* geometryFile = "");
        ~ShaderMgr();

        //Set uniform functions
        void Use(){ glUseProgram(this->m_ID); }

        void UnUse(){ glUseProgram(0); }

        /*Helpers Functions*/
        /*glUniform1i*/
        void SetUniform1i(GLint value, const GLchar* name);
        

        /*glUniform1f*/
        void SetUniform1f(GLfloat value, const GLchar* name);
        

        /*glUniform2fv*/
        void SetVec2f(glm::fvec2 value, const GLchar* name);
        

        /*glUniform3fv*/
        void SetVec3f(glm::fvec3 value, const GLchar* name);
        

        /*glUniform4fv*/
        void SetVec4f(glm::fvec4 value, const GLchar* name);
        

        /*glUniformMatrix3fv*/
        void SetMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
        

        /*glUniformMatrix4fv*/
        void SetMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
        

        // Utility Uniform Functions Same as Before Eazy Def
        // ------------------------------------------------------------------------
        void SetBool(const std::string &name, bool value) const
        {
            glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
        }

        // ------------------------------------------------------------------------
        void SetInt(const std::string &name, int value) const
        {
            glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
        }

        // ------------------------------------------------------------------------
        void SetFloat(const std::string &name, float value) const
        {
            glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
        }

    private:

        //Private functions
        std::string LoadShaderSrc(char* fileName);
        

        GLuint LoadShader(GLenum type, char* fileName);
        

        void LinkShader(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);

        // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
        void CheckCompileErrors(unsigned int shader, std::string type);
        
       
    };

}