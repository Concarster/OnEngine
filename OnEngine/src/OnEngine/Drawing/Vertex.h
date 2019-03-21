#pragma once
#include <glm\glm.hpp>

namespace on
{
    struct Vertex4A
    {
        glm::vec3 v_Position;
        glm::vec3 v_Color;
        glm::vec2 v_TexCoord;
        glm::vec3 v_Normal;
    };

    struct Vertex3A
    {
        glm::vec3 v_Position;
        glm::vec3 v_Color;
        glm::vec2 v_TexCoord;
       
    };

    struct Vertex2A
    {
        glm::vec3 v_Position;
        glm::vec3 v_Color;
       
    };

    struct Vertex
    {
        glm::vec3 v_Position;
        glm::vec3 v_Color;
        glm::vec2 v_TexCoord;
    };

    struct VertexPosition
    {
        glm::vec3 v_VPosition;
    };

}