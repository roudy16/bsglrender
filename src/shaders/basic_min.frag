#version 100
precision highp float;
varying vec4 col;

void main()
{
  gl_FragColor = vec4(col.rgb, 1.0);
}
