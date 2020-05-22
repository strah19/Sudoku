#include "Mouse.h"

bool MouseHandler::init()
{
	return true;
}

bool MouseHandler::destroy()
{
	return true;
}

bool MouseHandler::LeftClick(SDL_MouseButtonEvent& b)
{
	if (b.button == SDL_BUTTON_LEFT)
	{
		std::cout << "left";
		return true;
	}
	else
		return false;
}

bool MouseHandler::RightClick(SDL_MouseButtonEvent& b)
{
	if (b.button == SDL_BUTTON_RIGHT)
	{
		std::cout << "right";
		return true;
	}
	else
		return false;
}

bool MouseHandler::UpScrollWheel()
{
	if (gamePlay::mainEvent.wheel.y > 0)
	{
		return true;
	}

	return false;
}

bool MouseHandler::DownScrollWheel()
{

	if (gamePlay::mainEvent.wheel.y < 0)
	{
		return true;
	}

	return false;
}