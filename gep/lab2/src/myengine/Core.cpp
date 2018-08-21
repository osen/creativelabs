#include "Core.h"
#include "Entity.h"

namespace myengine
{

std::shared_ptr<Core> Core::initialize()
{
  std::shared_ptr<Core> rtn = std::make_shared<Core>();
  rtn->running = false;
  rtn->self = rtn;

  return rtn;
}

void Core::start()
{
  running = true;

  while(running)
  {
    for(std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
      it != entities.end(); it++)
    {
      (*it)->tick();
    }

    for(std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
      it != entities.end(); it++)
    {
      (*it)->display();
    }
  }
}

void Core::stop()
{
  running = false;
}

std::shared_ptr<Entity> Core::addEntity()
{
  std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
  entities.push_back(rtn);
  rtn->self = rtn;
  rtn->core = self;

  return rtn;
}

}
