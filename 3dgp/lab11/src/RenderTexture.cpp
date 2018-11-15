#include "RenderTexture.h"

RenderTexture::RenderTexture(int width, int height) : Texture(width, height)
{
  glGenFramebuffers(1, &fbo);
  if(!fbo) throw std::exception();
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);

  GLuint rbo = 0;
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint RenderTexture::getFbId()
{
  return fbo;
}

void RenderTexture::clear()
{
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
