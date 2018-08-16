uniform float in_Lightness;

varying vec4 ex_Color;

void main()
{
  gl_FragColor = ex_Color * in_Lightness;
}
