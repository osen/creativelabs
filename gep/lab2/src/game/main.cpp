#include <myengine/myengine.h>

#include <iostream>

class TestScreen : public myengine::Component
{
public:
  void onInit(std::string color)
  {
    std::cout << "onInit " << color << std::endl;
  }

  void onBegin()
  {
    std::cout << "onBegin" << std::endl;
  }

  void onTick()
  {
    std::cout << "onTick" << std::endl;

    getCore()->stop();
  }
};

int main()
{
  std::shared_ptr<myengine::Core> c = myengine::Core::initialize();
  std::shared_ptr<myengine::Entity> e = c->addEntity();
  std::shared_ptr<TestScreen> t = e->addComponent<TestScreen>("Green");

  c->start();

  return 0;
}
