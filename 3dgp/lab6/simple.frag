uniform sampler2D in_Texture;
uniform sampler2D in_Lightmap;
uniform int in_EnableMultiTex;

varying vec2 ex_TexCoord;

void main()
{
  vec4 col = texture2D(in_Texture, ex_TexCoord);

  if(in_EnableMultiTex != 0)
  {
    vec4 lm = texture2D(in_Lightmap, ex_TexCoord);
    col += lm;
  }

  gl_FragColor = col;
}
