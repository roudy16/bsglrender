#version 400
in vec3 position;
in vec4 color;

uniform mat4 mvp;

varying vec4 col;

void main()
{
  gl_Position = mvp * vec4(position, 1.0);
  col = color;
}
