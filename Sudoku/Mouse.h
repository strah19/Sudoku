#pragma once

#include "Main.h"
#include "InputSystem.h"

class MouseHandler
{
public:
	bool init();
	bool destroy();
	bool LeftClick(SDL_MouseButtonEvent& b);
	bool RightClick(SDL_MouseButtonEvent& b);

	bool UpScrollWheel();
	bool DownScrollWheel();

private:

};