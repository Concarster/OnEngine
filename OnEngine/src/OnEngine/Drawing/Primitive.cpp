#include "OnPCH.h"
#include "Primitive.h"

namespace on
{

    Primitive::Primitive()
    {
    }


    Primitive::~Primitive()
    {
    }

    void Primitive::SetVertices(const Vertex * vertices, const unsigned numOfVertices)
    {
        for (size_t i = 0; i < numOfVertices; i++)
        {
            this->m_Vertices.push_back(vertices[i]);
        }
    }

    void Primitive::SetVertices(const Vertex2A * vertices, const unsigned numOfVertices)
    {
        for (size_t i = 0; i < numOfVertices; i++)
        {
            this->m_Vertices2A.push_back(vertices[i]);
        }
    }

    void Primitive::SetVertices(const Vertex3A * vertices, const unsigned numOfVertices)
    {
        for (size_t i = 0; i < numOfVertices; i++)
        {
            this->m_Vertices3A.push_back(vertices[i]);
        }
    }

    void Primitive::SetVertices(const Vertex4A * vertices, const unsigned numOfVertices)
    {
        for (size_t i = 0; i < numOfVertices; i++)
        {
            this->m_Vertices4A.push_back(vertices[i]);
        }
    }

    void Primitive::SetIndices(const GLuint * indices, const unsigned int numOfIndices)
    {
        for (size_t i = 0; i < numOfIndices; i++)
        {
            this->m_Indices.push_back(indices[i]);
        }
    }

}