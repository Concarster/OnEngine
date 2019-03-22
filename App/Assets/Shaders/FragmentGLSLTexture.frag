#version 420

in vec3 vPosition;	
in vec3 vColor;
in vec2 vTextCoord;

out vec4 fragColor;

uniform sampler2D texture0;

void main()
{
   //fragColor = vec4(vColor, 1.0);
   //Using Texture
   
   fragColor = texture(texture0, vTextCoord);
   
   //Ignoring The color from the Vertex Atrrib
   //fragColor = vec4(1.0, 0.0, 0.0, 1.0);
};
