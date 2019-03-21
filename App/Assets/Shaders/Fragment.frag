#version 420

in vec3 vs_Position;
in vec3 vs_Color;
in vec2 vs_TextCoord;

// Ouput data
out vec4 fs_Color;

void main()
{
	// Output Color = Red 
	//fs_Color = vec4(1.0, 0.0, 0.0, 1.0);
	fs_Color = vec4(vs_Color, 1.0);
}