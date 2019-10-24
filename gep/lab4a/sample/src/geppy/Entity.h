#pragma once
#include "Component.h"
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Entity
{
public:
	
	template <typename T>
	std::shared_ptr<T> addComponent()
	{
		std::shared_ptr<T> rtn = std::make_shared<T>();

		components.push_back(rtn);

		return rtn;
	}

	void display();

private:
	std::vector<std::shared_ptr<Component>> components;


};
