uniform sampler2D in_Texture;
uniform sampler2D in_Lightmap;

varying vec2 ex_TexCoord;

void main()
{
  vec4 tex = texture(in_Texture, ex_TexCoord);
  vec4 lm = texture(in_Lightmap, ex_TexCoord);
  lm *= 1;
  vec4 col = tex + lm;
  gl_FragColor = col;
}