uniform sampler2D in_Texture;
uniform vec3 in_LightPos;
uniform mat4 in_Model;

varying vec2 ex_TexCoord;
varying vec3 ex_Normal;
varying vec3 ex_FragPos;

void main()
{
  vec4 tex = texture2D(in_Texture, ex_TexCoord);

  //vec3 wsNormal = mat3(transpose(inverse(in_Model))) * ex_Normal;
  //vec3 norm = normalize(wsNormal);
  vec3 norm = normalize(ex_Normal);
  vec3 lightDir = normalize(in_LightPos - ex_FragPos);

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * vec3(1, 1, 1);

  vec3 lighting = diffuse;

  gl_FragColor = vec4(lighting, 1) * tex;
}
