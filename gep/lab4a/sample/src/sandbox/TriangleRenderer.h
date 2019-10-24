#include <geppy/geppy.h>

#include <GL/glew.h>

struct TriangleRenderer : public Component
{
  TriangleRenderer();
  ~TriangleRenderer();

  void onDisplay();

private:
  SDL_Window* window;
  GLuint programId;
  GLuint vaoId;

};
