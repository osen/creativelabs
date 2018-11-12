#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>

#include <exception>

#define RENDER_TEXTURE_SIZE 512

int main(int argc, char *argv[])
{
  int windowWidth = 800;
  int windowHeight = 600;

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Lab 9 - Render Texture",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    windowWidth, windowHeight,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if(!SDL_GL_CreateContext(window))
  {
    throw std::exception();
  }

  if(glewInit() != GLEW_OK)
  {
    throw std::exception();
  }

  // Load shapes, textures and shaders from files
  VertexArray *hallShape = new VertexArray("re_hall_baked.obj");
  Texture *hallTexture = new Texture("re_hall_diffuse.png");
  VertexArray *shape = new VertexArray("curuthers.obj");
  Texture *texture = new Texture("curuthers_diffuse.png");
  ShaderProgram *shader = new ShaderProgram("simple.vert", "simple.frag");

  // Create UI shape
  VertexBuffer *positions = new VertexBuffer();
  positions->add(glm::vec3(0.0f, 1.0f, 0.0f));
  positions->add(glm::vec3(0.0f, 0.0f, 0.0f));
  positions->add(glm::vec3(1.0f, 0.0f, 0.0f));
  positions->add(glm::vec3(1.0f, 0.0f, 0.0f));
  positions->add(glm::vec3(1.0f, 1.0f, 0.0f));
  positions->add(glm::vec3(0.0f, 1.0f, 0.0f));

  VertexBuffer *texCoords = new VertexBuffer();
  texCoords->add(glm::vec2(0.0f, 0.0f));
  texCoords->add(glm::vec2(0.0f, -1.0f));
  texCoords->add(glm::vec2(1.0f, -1.0f));
  texCoords->add(glm::vec2(1.0f, -1.0f));
  texCoords->add(glm::vec2(1.0f, 0.0f));
  texCoords->add(glm::vec2(0.0f, 0.0f));

  VertexArray *uiShape = new VertexArray();
  uiShape->setBuffer("in_Position", positions);
  uiShape->setBuffer("in_TexCoord", texCoords);

  // Create framebuffer texture and depth attachment
  GLuint fbo = 0;
  glGenFramebuffers(1, &fbo);
  if(!fbo) throw std::exception();
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  GLuint fbt = 0;
  glGenTextures(1, &fbt);
  glBindTexture(GL_TEXTURE_2D, fbt);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, RENDER_TEXTURE_SIZE, RENDER_TEXTURE_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbt, 0);

  GLuint rbo = 0;
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, RENDER_TEXTURE_SIZE, RENDER_TEXTURE_SIZE);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  bool quit = false;
  float angle = 0;

  while(!quit)
  {
    SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, RENDER_TEXTURE_SIZE, RENDER_TEXTURE_SIZE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     * Draw with perspective projection matrix
     */
    shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     (float)RENDER_TEXTURE_SIZE / (float)RENDER_TEXTURE_SIZE, 0.1f, 100.f));

    // Create a "camera"
    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
    shader->setUniform("in_View", glm::inverse(model));

    // Draw the mansion
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, -2.0f, -16.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
    shader->setUniform("in_Model", model);
    shader->setUniform("in_Texture", hallTexture);
    shader->draw(hallShape);

    // Draw the cat
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, -2.1f, -20.0f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
    shader->setUniform("in_Model", model);
    shader->setUniform("in_Texture", texture);
    shader->draw(shape);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    // Draw with orthographic projection matrix
    shader->setUniform("in_Projection", glm::ortho(0.0f,
     (float)windowWidth, 0.0f, (float)windowHeight, 0.0f, 1.0f));

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(50, windowHeight - 200 - 50, 0));
    model = glm::scale(model, glm::vec3(200, 200, 1));

    shader->setUniform("in_View", glm::mat4(1.0f));
    shader->setUniform("in_Model", model);
    shader->setUniform("in_Texture", 1);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, fbt);
    glBindVertexArray(uiShape->getId());
    glUseProgram(shader->getId());
    glDrawArrays(GL_TRIANGLES, 0, uiShape->getVertexCount());

    angle+=0.01f;

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
