#include "Entity.h"

#include <memory>
#include <iostream>

class Core
{
public:
	std::shared_ptr<Entity> addEntity();
	void run();
	
	static std::shared_ptr<Core> initialize();

private:
	std::vector<std::shared_ptr<Entity> > entities;

};
