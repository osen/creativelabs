uniform mat4 in_Projection;
uniform mat4 in_Model;

attribute vec3 in_Position;
attribute vec4 in_Color;

varying vec4 ex_Color;

void main()
{
  gl_Position = in_Projection * in_Model * vec4(in_Position, 1.0);
  ex_Color = in_Color;
}

