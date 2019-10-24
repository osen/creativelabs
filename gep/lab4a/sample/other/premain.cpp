#include <geppy/geppy.h>

#include <iostream>
#include <memory>

class TriangleRenderer : public Component
{
	void onDisplay()
	{
		std::cout << "Hello Triangle" << std::endl;
	}
};

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> entity = core->addEntity();
	std::shared_ptr<TriangleRenderer> tr = entity->addComponent<TriangleRenderer>();

	core->run();

	return 0;
}
