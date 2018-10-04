#include "Component.h"

#include <memory>
#include <vector>

#define ADDCOMPONENT \
  std::shared_ptr<T> rtn = std::make_shared<T>(); \
  rtn->entity = self; \
  rtn->began = false; \
  components.push_back(rtn);

namespace myengine
{

class Core;

class Entity
{
  friend class Core;

public:
  template <typename T>
  std::shared_ptr<T> addComponent()
  {
    ADDCOMPONENT
    rtn->onInit();

    return rtn;
  }

  template <typename T, typename A>
  std::shared_ptr<T> addComponent(A a)
  {
    ADDCOMPONENT
    rtn->onInit(a);

    return rtn;
  }

  template <typename T, typename A, typename B>
  std::shared_ptr<T> addComponent(A a, B b)
  {
    ADDCOMPONENT
    rtn->onInit(a, b);

    return rtn;
  }

  std::shared_ptr<Core> getCore();

private:
  std::weak_ptr<Entity> self;
  std::weak_ptr<Core> core;
  std::vector<std::shared_ptr<Component> > components;

  void tick();
  void display();

};

}
