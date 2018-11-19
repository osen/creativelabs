#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class VertexArray;
class Texture;
class RenderTexture;

struct Sampler
{
  GLint id;
  Texture *texture;
};

class ShaderProgram
{
  GLuint id;
  std::vector<Sampler> samplers;
  glm::vec4 viewport;
  VertexArray *simpleShape;

public:
  ShaderProgram(std::string vert, std::string frag);
  void draw();
  void draw(RenderTexture *renderTexture);
  void draw(VertexArray *vertexArray);
  void draw(RenderTexture *renderTexture, VertexArray *vertexArray);
  void setUniform(std::string uniform, glm::vec4 value);
  void setUniform(std::string uniform, float value);
  void setUniform(std::string uniform, int value);
  void setUniform(std::string uniform, glm::mat4 value);
  void setUniform(std::string uniform, Texture *texture);
  GLuint getId();
  void setViewport(glm::vec4 viewport);

};
