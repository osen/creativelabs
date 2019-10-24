#include "Entity.h"

void Entity::display()
{
	for(size_t i = 0; i < components.size(); i++)
	{
		components.at(i)->onDisplay();
	}
}
