#include "InputSystem.h"
#include <cassert>

InputSystem::InputSystem()
{
	numBinds = 0;
}

bool InputSystem::init()
{
	for (int i = 0; i < numBinds; i++)
	{
		keyboard[i]->ID = i;
	}
	return true;
}

InputSystem::~InputSystem()
{
	for (int i = 0; i < numBinds; i++)
	{
		delete keyboard[i];
	}
}


void InputSystem::addKey(int num)
{
	numBinds = num;
	for (int i = 0; i < numBinds; i++)
	{
		keyboard[i] = new keyBoardHandler;
		keyboard[i]->parentInput = this;
	}
}

void InputSystem::setKey(Keys::listOfKeys k, int ID)
{
	keyboard[ID]->bind(k);
}

bool InputSystem::update(int ID)
{
	for (int i = 0; i < numBinds; i++)
	{

		if (ID == keyboard[i]->ID)
		{
			return keyboard[i]->update();
		}
		
	}
	return false;
}