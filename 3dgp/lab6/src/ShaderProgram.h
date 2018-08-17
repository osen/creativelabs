#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class VertexArray;
class Texture;

struct Sampler
{
  GLint id;
  Texture *texture;
};

class ShaderProgram
{
  GLuint id;
  std::vector<Sampler> samplers;

public:
  ShaderProgram(std::string vert, std::string frag);
  void draw(VertexArray *vertexArray);
  void setUniform(std::string uniform, glm::vec4 value);
  void setUniform(std::string uniform, float value);
  void setUniform(std::string uniform, glm::mat4 value);
  void setUniform(std::string uniform, Texture *texture);
  GLuint getId();

};
