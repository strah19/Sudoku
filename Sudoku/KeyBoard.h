#pragma once

#include "Main.h"
#include "InputSystem.h"

class keyBoardHandler
{
public:
	void bind(Keys::listOfKeys k);
	bool update();
private:
	friend class InputSystem;
	InputSystem* parentInput;

	const Uint8* state = SDL_GetKeyboardState(NULL);
	Keys::listOfKeys whichKey;
	int ID;
};