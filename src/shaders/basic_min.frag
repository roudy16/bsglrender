#version 400
precision highp float;
varying vec4 col;

out vec4 color;

void main()
{
  color = vec4(col.rgb, 1.0);
}
