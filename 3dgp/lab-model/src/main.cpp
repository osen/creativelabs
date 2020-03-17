#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <bugl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <exception>
#include <iostream>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512

const GLfloat positions[] = {
  -0.5f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.5f, 0.5f, 0.0f,
  -0.5f, 0.5f, 0.0f
};

const GLfloat texCoords[] = {
  0.0f, 0.0f,
  0.0f, 1.0f,
  1.0f, 1.0f,
  1.0f, 1.0f,
  1.0f, 0.0f,
  0.0f, 0.0f
};

const GLchar *vertexShaderSrc =
  "attribute vec3 a_Position;" \
  "attribute vec2 a_TexCoord;" \
  "" \
  "uniform mat4 u_Projection;" \
  "uniform mat4 u_Model;" \
  "" \
  "varying vec2 v_TexCoord;" \
  "" \
  "void main()" \
  "{" \
  "  v_TexCoord = a_TexCoord;" \
  "  gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0);" \
  "}" \
  "";

const GLchar *fragmentShaderSrc =
  "uniform sampler2D u_Texture;" \
  "" \
  "varying vec2 v_TexCoord;" \
  "" \
  "void main()" \
  "{" \
  "  vec4 col = texture2D(u_Texture, v_TexCoord);" \
  "  gl_FragColor = col;" \
  "}" \
  "";

GLuint programId;
GLuint vaoId;
GLuint texCoordsVboId;
GLuint positionsVboId;

GLuint mvaoId;
size_t verts;

bool quit;
SDL_Window *window;
float lastTime;
float rotation;
bool enableCull;
bool enableBlend = true;

void loop()
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
      if(event.key.keysym.sym == SDLK_b)
      {
        enableBlend = !enableBlend;
      }
      else if(event.key.keysym.sym == SDLK_c)
      {
        enableCull = !enableCull;
      }
    }
  }

  float now = SDL_GetTicks();
  float deltaTime = (now - lastTime) / 1000.0f;
  lastTime = now;

  rotation += 90.0f * deltaTime;

  glm::mat4 projection = glm::perspective(glm::radians(45.0f),
    (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(0, 0, -10));
  model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 1, 0));

  glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(programId);
  //glBindVertexArray(vaoId);
  glBindVertexArray(mvaoId);

  glUniformMatrix4fv(glGetUniformLocation(programId, "u_Projection"),
    1, GL_FALSE, glm::value_ptr(projection));

  glUniformMatrix4fv(glGetUniformLocation(programId, "u_Model"),
    1, GL_FALSE, glm::value_ptr(model));

  if(enableCull)
  {
    glEnable(GL_CULL_FACE);
  }

  if(enableBlend)
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  glEnable(GL_DEPTH_TEST);

  //glDrawArrays(GL_TRIANGLES, 0, 6);
  glDrawArrays(GL_TRIANGLES, 0, verts);

  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);

  glBindVertexArray(0);
  glUseProgram(0);

  SDL_GL_SwapWindow(window);
}

int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  window = SDL_CreateWindow("OpenGL Sample",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if(!SDL_GL_CreateContext(window))
  {
    throw std::exception();
  }

  if(glewInit() != GLEW_OK)
  {
    throw std::exception();
  }

  // Create a new VBO on the GPU and bind it
  glGenBuffers(1, &positionsVboId);

  if(!positionsVboId)
  {
    throw std::exception();
  }

  glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

  // Upload a copy of the data from memory into the new VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

  // Reset the state
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Create a new VBO on the GPU and bind it
  glGenBuffers(1, &texCoordsVboId);

  if(!texCoordsVboId)
  {
    throw std::exception();
  }

  glBindBuffer(GL_ARRAY_BUFFER, texCoordsVboId);

  // Upload a copy of the data from memory into the new VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

  // Reset the state
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  vaoId = 0;

  // Create a new VAO on the GPU and bind it
  glGenVertexArrays(1, &vaoId);

  if(!vaoId)
  {
    throw std::exception();
  }

  glBindVertexArray(vaoId);

  // Bind the position VBO, assign it to position 0 on the bound
  // VAO and flag it to be used
  glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, texCoordsVboId);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(1);

  // Reset the state
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  mvaoId = buLoadModel("resources/curuthers.obj", &verts);

  GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
  glCompileShader(vertexShaderId);
  GLint success = 0;
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    std::cout << "Failed to compile vertex shader" << std::endl;
    throw std::exception();
  }

  GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
  glCompileShader(fragmentShaderId);
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    std::cout << "Failed to compile fragment shader" << std::endl;
    throw std::exception();
  }

  programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glBindAttribLocation(programId, 0, "a_Position");
  glBindAttribLocation(programId, 1, "a_TexCoord");

  if(glGetError() != GL_NO_ERROR)
  {
    throw std::exception();
  }

  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &success);

  if(!success)
  {
    throw std::exception();
  }

  glDetachShader(programId, vertexShaderId);
  glDeleteShader(vertexShaderId);
  glDetachShader(programId, fragmentShaderId);
  glDeleteShader(fragmentShaderId);

  int imgWidth = 0;
  int imgHeight = 0;

  //unsigned char *data = stbi_load("resources/sample.png",
  //  &imgWidth, &imgHeight, NULL, 4);

  unsigned char *data = stbi_load("resources/Whiskers_diffuse.png",
    &imgWidth, &imgHeight, NULL, 4);

  if(!data)
  {
    throw std::exception();
  }

  GLuint texId = 0;
  glGenTextures(1, &texId);

  if(!texId)
  {
    throw std::exception();
  }

  glBindTexture(GL_TEXTURE_2D, texId);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight,
    0, GL_RGBA, GL_UNSIGNED_BYTE, data);

  free(data);
  glGenerateMipmap(GL_TEXTURE_2D);

  while(!quit)
  {
    loop();
  }

  glDeleteProgram(programId);
  glDeleteVertexArrays(1, &vaoId);
  glDeleteBuffers(1, &positionsVboId);
  glDeleteBuffers(1, &texCoordsVboId);
  glDeleteVertexArrays(1, &vaoId);
  glDeleteVertexArrays(1, &mvaoId);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
