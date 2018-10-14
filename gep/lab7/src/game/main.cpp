#include <myengine/myengine.h>

#include <iostream>

class TestScreen : public myengine::Component
{
public:
  void onInit(std::string color)
  {
    //std::cout << "onInit " << color << std::endl;
  }

  void onBegin()
  {
    //std::cout << "onBegin" << std::endl;
  }

  void onTick()
  {
    throw myengine::Exception("I decided to throw...");
    //std::cout << "onTick" << std::endl;
  }

  void onDisplay()
  {
    //std::cout << "onTick" << std::endl;
  }
};

int main()
{
  std::shared_ptr<myengine::Core> c = myengine::Core::initialize();

  std::shared_ptr<myengine::Entity> e = c->addEntity();

  std::shared_ptr<myengine::Sound> s = std::make_shared<myengine::Sound>("dixie_horn.ogg");
  s->play();

  std::shared_ptr<TestScreen> ts = e->addComponent<TestScreen>("Green");
  std::shared_ptr<myengine::MeshRenderer> mr = e->addComponent<myengine::MeshRenderer>();
  std::shared_ptr<myengine::MeshRenderer> mr2 = e->getComponent<myengine::MeshRenderer>();

  try
  {
    c->start();
  }
  catch(myengine::Exception& e)
  {
    std::cout << "MyEngine Exception: " << e.what() << std::endl;
  }
  catch(std::exception& e)
  {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cout << "An unknown object was thrown" << std::endl;
  }

  return 0;
}
