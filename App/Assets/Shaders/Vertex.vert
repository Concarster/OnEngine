#version 420

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Color;
layout(location = 2) in vec2 v_TextCoord;

out vec3 vs_Position;
out vec3 vs_Color;
out vec2 vs_TextCoord;

void main()
{
    vs_Position = v_Position;
    vs_Color = v_Color;
    vs_TextCoord = vec2(v_TextCoord.x, v_TextCoord.y * - 1.0);

    gl_Position = vec4(v_Position * 1.0);
}

