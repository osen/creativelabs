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

};

}
