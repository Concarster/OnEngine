#include "OnPCH.h"
#include "Material.h"

namespace on
{

    Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex )
    {
        this->m_Ambient      = ambient;
        this->m_Diffuse      = diffuse;
        this->m_Specular     = specular;
        this->m_DiffuseTex   = diffuseTex;
        this->m_SpecularTex  = specularTex;
    }


    Material::~Material()
    {
    }

    void Material::SendToShader(ShaderMgr & program)
    {
        program.SetVec3f(this->m_Ambient,  "material.ambient");
        program.SetVec3f(this->m_Diffuse,  "material.diffuse");
        program.SetVec3f(this->m_Specular, "material.specular");

        program.SetUniform1i(this->m_DiffuseTex,  "material.diffuseTex");
        program.SetUniform1i(this->m_SpecularTex, "material.specularTex");
    }

}
