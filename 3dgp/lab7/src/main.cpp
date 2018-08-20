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

  SDL_Window *window = SDL_CreateWindow("Lab 7 - Camera",
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

  VertexArray *hallShape = new VertexArray("re_hall_baked.obj");
  Texture *hallTexture = new Texture("re_hall_diffuse.png");
  VertexArray *shape = new VertexArray("curuthers.obj");
  Texture *texture = new Texture("curuthers_diffuse.png");
  ShaderProgram *shader = new ShaderProgram("simple.vert", "simple.frag");

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     * Draw with perspective projection matrix
     */
    shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     (float)windowWidth / (float)windowHeight, 0.1f, 100.f));

    // Draw the mansion
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, -2.0f, -16.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
    shader->setUniform("in_Model", model);
    shader->setUniform("in_Texture", hallTexture);
    shader->draw(hallShape);

    // Draw the cat
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, -2, -20.0f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
    shader->setUniform("in_Model", model);
    shader->setUniform("in_Texture", texture);
    shader->draw(shape);

    angle++;

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
