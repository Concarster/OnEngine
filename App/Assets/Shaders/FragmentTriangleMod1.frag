#version 330 core

in vec3 fragmentColor;

// Ouput data
//out vec4 FragColor;
out vec3 color;

    void main()
    {
       //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	   color = fragmentColor;
    };
