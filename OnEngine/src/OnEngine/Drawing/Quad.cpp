#include "OnPCH.h"
#include "Quad.h"

namespace on
{

    Quad::Quad()
        :Primitive()
    {
        Vertex4A vertices[] =
        {
            //Position								//Color							//Texcoords					//Normals
            glm::vec3(-0.5f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.5f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)
        };
        unsigned numbOfVertices = sizeof(vertices) / sizeof(Vertex4A);

        GLuint indices[] =
        {
            0, 1, 2,	//Triangle 1
            0, 2, 3		//Triangle 2
        };
        unsigned numbOfIndices = sizeof(indices) / sizeof(GLuint);

        this->SetVertices(vertices, numbOfVertices);
        this->SetIndices(indices, numbOfIndices);
    }


    Quad::~Quad()
    {
    }

}