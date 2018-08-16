#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <exception>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

const GLfloat positions[] = {
  0.0f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f
};

const GLfloat colors[] = {
  1.0f, 0.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f
};

const GLchar *vertexShaderSrc =
  "attribute vec3 in_Position;" \
  "attribute vec4 in_Color;" \
  "" \
  "varying vec4 ex_Color;" \
  "" \
  "void main()" \
  "{" \
  "  gl_Position = vec4(in_Position, 1.0);" \
  "  ex_Color = in_Color;" \
  "}" \
  "";

const GLchar *fragmentShaderSrc =
  "varying vec4 ex_Color;" \
  "void main()" \
  "{" \
  "  gl_FragColor = ex_Color;" \
  "}" \
  "";

int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Triangle",
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

  GLuint positionsVboId = 0;

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

  GLuint colorsVboId = 0;

  // Create a colors VBO on the GPU and bind it
  glGenBuffers(1, &colorsVboId);

  if(!colorsVboId)
  {
    throw std::exception();
  }

  glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

  // Upload a copy of the data from memory into the new VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

  // Reset the state
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint vaoId = 0;

  // Create a new VAO on the GPU and bind it
  glGenVertexArrays(1, &vaoId);

  if(!vaoId)
  {
    throw std::exception();
  }

  glBindVertexArray(vaoId);

  // Bind the position VBO, assign it to position 0 on the bound VAO and flag it to be used
  glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
  glEnableVertexAttribArray(0);

  // Bind the color VBO, assign it to position 1 on the bound VAO and flag it to be used
  glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)0);
  glEnableVertexAttribArray(1);

  // Reset the state
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
  glCompileShader(vertexShaderId);
  GLint success = 0;
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    throw std::exception();
  }

  GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
  glCompileShader(fragmentShaderId);
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    throw std::exception();
  }

  GLuint programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glBindAttribLocation(programId, 0, "in_Position");
  glBindAttribLocation(programId, 1, "in_Color");

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

  bool quit = false;

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

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programId);
    glBindVertexArray(vaoId);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
