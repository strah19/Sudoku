#pragma once

#include "Main.h"
#include "KeyBoard.h"

class keyBoardHandler;

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	bool init();
	bool destroy() { return true; }
	void addKey(int num);

	void setKey(Keys::listOfKeys k, int ID);
	bool update(int ID);
private:
	static const int maxBinds = 15;
	keyBoardHandler* keyboard[maxBinds];
	int numBinds;
};