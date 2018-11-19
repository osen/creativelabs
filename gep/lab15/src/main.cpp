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
  ShaderProgram *lightkeyShader = new ShaderProgram("lightkeypass.vert", "lightkeypass.frag");
  ShaderProgram *nullShader = new ShaderProgram("nullpass.vert", "nullpass.frag");
  ShaderProgram *blurShader = new ShaderProgram("blur.vert", "blur.frag");
  ShaderProgram *mergeShader = new ShaderProgram("mergepass.vert", "mergepass.frag");
  RenderTexture *rt = new RenderTexture(1024, 1024);
  RenderTexture *lightkeyRt = new RenderTexture(1024, 1024);
  RenderTexture *blurRt = new RenderTexture(1024, 1024);
  RenderTexture *blur2Rt = new RenderTexture(1024, 1024);
  RenderTexture *blur3Rt = new RenderTexture(1024, 1024);
  RenderTexture *mergeRt = new RenderTexture(1024, 1024);

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

    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    rt->clear();

    /*
     * Draw with perspective projection matrix
     */
    shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     (float)windowWidth / (float)windowHeight, 0.1f, 100.f));

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
    //glClear(GL_COLOR_BUFFER_BIT);

    lightkeyShader->setUniform("in_Texture", rt);
    lightkeyShader->draw(lightkeyRt);

    blurShader->setUniform("in_Texture", lightkeyRt);
    blurShader->draw(blurRt);

    blurShader->setUniform("in_Texture", blurRt);
    blurShader->draw(blur2Rt);

    blurShader->setUniform("in_Texture", blur2Rt);
    blurShader->draw(blur3Rt);

    mergeShader->setUniform("in_TextureA", rt);
    mergeShader->setUniform("in_TextureB", blur3Rt);
    mergeShader->draw(mergeRt);

    nullShader->setViewport(glm::vec4(0, 0, windowWidth, windowHeight));
    nullShader->setUniform("in_Texture", rt);
    nullShader->draw();

    angle+=0.01f;

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
