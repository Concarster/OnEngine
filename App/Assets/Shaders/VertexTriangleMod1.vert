#version 330 core
    layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 vertexColor;
	

out vec3 fragmentColor;     // Output data ; will be interpolated for each fragment.
	
    void main()
    {
       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	   fragmentColor = vertexColor;
    };

