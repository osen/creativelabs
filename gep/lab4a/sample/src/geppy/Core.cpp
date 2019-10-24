#include "Core.h"

std::shared_ptr<Core> Core::initialize()
{
	std::shared_ptr<Core> c = std::make_shared<Core>();
	return c;
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

	entities.push_back(rtn);

	return rtn;
}

void Core::run()
{
	while(true)
	{
		for(size_t i = 0; i < entities.size(); i++)
		{
			entities.at(i)->display();
		}
	}
}
