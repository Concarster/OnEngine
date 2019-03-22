#version 420

layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec3 vertColor;
layout (location = 2) in vec2 vertTextCoord;

out vec3 vPosition;	
out vec3 vColor;
out vec2 vTextCoord;

void main()
{
   vPosition  = vertPosition;
   vColor     = vertColor;
   vTextCoord = vec2(vertTextCoord.x, vertTextCoord.y * - 1.0);

   //gl_Position = vec4(vertPosition + 0.3, 1.0);
   //gl_Position = vec4(vertPosition - 0.3, 1.0);
   //gl_Position = vec4(vertPosition.x + 0.48, vertPosition.y + 0.48, vertPosition.z, 1.0);
   gl_Position = vec4(vertPosition, 1.0);
};

