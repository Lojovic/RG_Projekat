#version 330 core
out vec4 FragColor;
in vec2 outTexCoords;

uniform sampler2D image;
//uniform vec3 spriteColor;

void main()
{
  FragColor = texture(image, outTexCoords);
}

