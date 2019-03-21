#pragma once
#include <glad\glad.h>
#include "OnEngine/Util/Defs.h"
#include "Vertex.h"

namespace on
{

    class ON_API Primitive
    {
    private:
        std::vector<Vertex4A> m_Vertices4A;
        std::vector<Vertex> m_Vertices;
        std::vector<GLuint> m_Indices;
    public:
        Primitive();
        ~Primitive();

        /*Function*/
        void SetVertices(const Vertex* vertices, const unsigned numOfVertices);
 
        void SetVertices(const Vertex4A* vertices, const unsigned numOfVertices);

        void SetIndices(const GLuint* indices, const unsigned int numOfIndices);


        inline Vertex* GetVertices() { return this->m_Vertices.data(); }

        inline Vertex4A* GetVertices4A() { return this->m_Vertices4A.data(); }

        inline GLuint* GetIndices() { return this->m_Indices.data(); }

        inline const unsigned GetNumOfVertices() { return this->m_Vertices.size(); }
        inline const unsigned GetNumOfIndices() { return this->m_Indices.size(); }

    };

}