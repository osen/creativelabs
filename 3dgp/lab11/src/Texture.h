#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

class RenderTexture;

class Texture
{
  friend class RenderTexture;

  GLuint id;
  glm::vec2 size;

  Texture(int width, int height);

public:
  Texture(std::string path);
  glm::vec2 getSize();
  GLuint getId();

};

#endif
