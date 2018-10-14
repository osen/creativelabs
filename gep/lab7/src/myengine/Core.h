#include <SDL2/SDL.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <vector>

namespace myengine
{

class Entity;

class Core
{
public:
  static std::shared_ptr<Core> initialize();

  void start();
  void stop();
  std::shared_ptr<Entity> addEntity();

private:
  bool running;
  std::vector<std::shared_ptr<Entity> > entities;
  std::weak_ptr<Core> self;

  SDL_Window *window;
  ALCdevice* device;
  ALCcontext* context;

};

}
