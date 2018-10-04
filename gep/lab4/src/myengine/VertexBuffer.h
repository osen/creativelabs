#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

namespace myengine
{

class VertexBuffer
{
  GLuint id;
  int components;
  std::vector<GLfloat> data;
  bool dirty;

public:
  VertexBuffer();
  void add(glm::vec3 value);
  void add(glm::vec4 value);
  int getComponents();
  int getDataSize();
  GLuint getId();

};

}
