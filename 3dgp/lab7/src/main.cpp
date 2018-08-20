#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>

#include <exception>

int windowWidth = 800;
int windowHeight = 600;

int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Camera",
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

  VertexArray *shape = new VertexArray("curuthers.obj");
  ShaderProgram *shader = new ShaderProgram("simple.vert", "simple.frag");
  Texture *texture = new Texture("curuthers_diffuse.png");
  shader->setUniform("in_Texture", texture);

  bool quit = false;
  float angle = 0;

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

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

    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 model(1.0f);

    // Draw with perspective projection matrix
    shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     (float)windowWidth / (float)windowHeight, 0.1f, 100.f));

    model = glm::translate(model, glm::vec3(0, 0, -10.0f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

    shader->setUniform("in_Model", model);
    shader->draw(shape);

    // Draw with orthographic projection matrix
    model = glm::mat4(1.0f);

    shader->setUniform("in_Projection", glm::ortho(0.0f,
     (float)windowWidth, 0.0f, (float)windowHeight, 0.0f, 1.0f));

    model = glm::translate(model, glm::vec3(100, windowHeight - 100, 0));
    model = glm::scale(model, glm::vec3(100, 100, 1));

    shader->setUniform("in_Model", model);
    shader->draw(shape);

    angle++;

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
