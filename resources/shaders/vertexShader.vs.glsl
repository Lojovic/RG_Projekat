#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoords;

out vec2 outTexCoords;
out vec3 outNormals;
out vec3 outFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  outFragPos = vec3(model * vec4(aPos, 1.0));
  outNormals = mat3(transpose(inverse(model))) * aNormals;
  outTexCoords = vec2(aTexCoords.x,1.0f - aTexCoords.y);

  gl_Position = projection * view * vec4(outFragPos, 1.0f);
}
