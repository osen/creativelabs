#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

class VertexBuffer;

class VertexArray
{
  GLuint id;
  bool dirty;
  std::vector<VertexBuffer *> buffers;

public:
  VertexArray();
  void setBuffer(std::string attribute, VertexBuffer *buffer);
  int getVertexCount();
  GLuint getId();

};
