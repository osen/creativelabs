#ifndef MYENGINE_COMPONENT_H
#define MYENGINE_COMPONENT_H

#include <memory>

namespace myengine
{

class Entity;
class Core;

class Component
{
  friend class Entity;

public:
  std::shared_ptr<Core> getCore();
  std::shared_ptr<Entity> getEntity();

private:
  std::weak_ptr<Entity> entity;
  bool began;

  virtual void onInit();
  virtual void onBegin();
  virtual void onTick();
  virtual void onDisplay();
};

}

#endif
