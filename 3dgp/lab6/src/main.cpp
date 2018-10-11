#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>

#include <exception>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Multitexturing",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if(!SDL_GL_CreateContext(window))
  {
    throw std::exception();
  }

  if(glewInit() != GLEW_OK)
  {
    throw std::exception();
  }

  VertexBuffer *positions = new VertexBuffer();
  positions->add(glm::vec3(-0.5f, 0.5f, 0.0f));
  positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
  positions->add(glm::vec3(0.5f, -0.5f, 0.0f));
  positions->add(glm::vec3(0.5f, -0.5f, 0.0f));
  positions->add(glm::vec3(0.5f, 0.5f, 0.0f));
  positions->add(glm::vec3(-0.5f, 0.5f, 0.0f));

  VertexBuffer *texCoords = new VertexBuffer();
  texCoords->add(glm::vec2(0.0f, 0.0f));
  texCoords->add(glm::vec2(0.0f, 1.0f));
  texCoords->add(glm::vec2(1.0f, 1.0f));
  texCoords->add(glm::vec2(1.0f, 1.0f));
  texCoords->add(glm::vec2(1.0f, 0.0f));
  texCoords->add(glm::vec2(0.0f, 0.0f));

  VertexArray *shape = new VertexArray();
  shape->setBuffer("in_Position", positions);
  shape->setBuffer("in_TexCoord", texCoords);

  ShaderProgram *shader = new ShaderProgram("simple.vert", "simple.frag");
  Texture *texture = new Texture("texture.png");
  Texture *lightmap = new Texture("lightmap.png");
  shader->setUniform("in_Texture", texture);
  shader->setUniform("in_Lightmap", lightmap);

  bool quit = false;
  float angle = 0;
  int multiTex = 0;

  while(!quit)
  {
    SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
      else if(event.type == SDL_KEYDOWN)
      {
        multiTex = !multiTex;
        shader->setUniform("in_EnableMultiTex", multiTex);
      }
    }

    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glm::mat4 model(1.0f);

    // Draw with perspective projection matrix
    shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));

    model = glm::translate(model, glm::vec3(0, 0, -1.5f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

    shader->setUniform("in_Model", model);
    shader->draw(shape);

    // Draw with orthographic projection matrix
    model = glm::mat4(1.0f);

    shader->setUniform("in_Projection", glm::ortho(0.0f,
     (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.0f, 1.0f));

    model = glm::translate(model, glm::vec3(100, WINDOW_HEIGHT - 100, 0));
    model = glm::scale(model, glm::vec3(100, 100, 1));

    shader->setUniform("in_Model", model);
    shader->draw(shape);

    angle+=0.1f;

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
