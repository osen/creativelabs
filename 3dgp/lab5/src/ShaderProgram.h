#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

class VertexArray;

class ShaderProgram
{
  GLuint id;

public:
  ShaderProgram(std::string vert, std::string frag);
  void draw(VertexArray *vertexArray);
  void setUniform(std::string uniform, glm::vec4 value);
  void setUniform(std::string uniform, float value);
  void setUniform(std::string uniform, glm::mat4 value);
  GLuint getId();

};
