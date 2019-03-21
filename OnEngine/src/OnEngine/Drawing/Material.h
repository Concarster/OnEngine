#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>


#include "ShaderMgr.h"

namespace on
{

    class Material
    {
    private:
        glm::vec3 m_Ambient;
        glm::vec3 m_Diffuse;
        glm::vec3 m_Specular;

        GLint m_DiffuseTex;
        GLint m_SpecularTex;

    public:
        Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex);
        ~Material();

        //Function
        void SendToShader(ShaderMgr& program);
    };

}