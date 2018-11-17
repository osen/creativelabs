uniform sampler2D in_TextureA;
uniform sampler2D in_TextureB;

varying vec2 ex_TexCoord;

void main()
{
  vec4 texA = texture2D(in_TextureA, ex_TexCoord);
  vec4 texB = texture2D(in_TextureB, ex_TexCoord);
  gl_FragColor = texA + texB;
}
