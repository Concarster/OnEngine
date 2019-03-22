#pragma once
#include <glad\glad.h>
#include "OnEngine/Util/Defs.h"
#include "Vertex.h"

namespace on
{

    class ON_API Primitive
    {
    private:
        std::vector<Vertex> m_Vertices;
        std::vector<Vertex2A> m_Vertices2A;
        std::vector<Vertex3A> m_Vertices3A;
        std::vector<Vertex4A> m_Vertices4A;

        std::vector<GLuint> m_Indices;

    public:
        Primitive();
        ~Primitive();

        /*Helpers Function to GET the Vertexs*/
        void SetVertices(const Vertex* vertices, const unsigned numOfVertices);

        void SetVertices(const Vertex2A* vertices, const unsigned numOfVertices);

        void SetVertices(const Vertex3A* vertices, const unsigned numOfVertices);
 
        void SetVertices(const Vertex4A* vertices, const unsigned numOfVertices);

        void SetIndices(const GLuint* indices, const unsigned int numOfIndices);


        inline Vertex*     GetVertices()   { return this->m_Vertices.data(); }
        inline Vertex2A*   GetVertices2A() { return this->m_Vertices2A.data(); }
        inline Vertex3A*   GetVertices3A() { return this->m_Vertices3A.data(); }
        inline Vertex4A*   GetVertices4A() { return this->m_Vertices4A.data(); }


        inline GLuint* GetIndices() { return this->m_Indices.data(); }

        inline const size_t  GetNumOfVertices()    { return this->m_Vertices.size(); }
        inline const size_t  GetNumOfVertices2A()  { return this->m_Vertices2A.size(); }
        inline const size_t  GetNumOfVertices3A()  { return this->m_Vertices3A.size(); }
        inline const size_t  GetNumOfVertices4A()  { return this->m_Vertices4A.size(); }

        inline const size_t GetNumOfIndices() { return this->m_Indices.size(); }

    };

}