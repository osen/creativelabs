#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "RenderTexture.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>

#include <exception>

int main(int argc, char *argv[])
{
  int windowWidth = 800;
  int windowHeight = 600;

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Lab 11 - Render Texture",
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
  RenderTexture *rt = new RenderTexture(512, 512);

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

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, rt->getSize().x, rt->getSize().y);
    rt->clear();

    /*
     * Draw with perspective projection matrix
     */
    shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     rt->getSize().x / rt->getSize().y, 0.1f, 100.f));

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
    shader->draw(rt, hallShape);

    // Draw the cat
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, -2.1f, -20.0f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
    shader->setUniform("in_Model", model);
    shader->setUniform("in_Texture", texture);
    shader->draw(rt, shape);

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    // Draw with orthographic projection matrix
    shader->setUniform("in_Projection", glm::ortho(0.0f,
     (float)windowWidth, 0.0f, (float)windowHeight, 0.0f, 1.0f));

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(50, windowHeight - 400 - 50, 0));
    model = glm::scale(model, glm::vec3(400, 400, 1));

    shader->setUniform("in_View", glm::mat4(1.0f));
    shader->setUniform("in_Model", model);
    shader->setUniform("in_Texture", rt);
    shader->draw(uiShape);

    angle+=0.01f;

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
