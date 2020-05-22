#include "KeyBoard.h"

void keyBoardHandler::bind(Keys::listOfKeys k)
{
	whichKey = k;
}

bool keyBoardHandler::update()
{
	if (state[whichKey])
	{
		return true;
	}

	return false;
}
