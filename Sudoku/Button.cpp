#include "Button.h"

bool ButtonComponent::init(const char* text, int x, int y, int w, int h)
{
	tex = textureMananger::LoadTexture(text);

	mainRect.x = x;
	mainRect.y = y;
	mainRect.w = w;
	mainRect.h = h;

	src.x = 0;
	src.y = 0;
	src.w = w;
	src.h = h;

	tempRect.x = x;
	tempRect.y = y;
	tempRect.w = w;
	tempRect.h = h;

	return true;
}

ButtonComponent::~ButtonComponent()
{
	SDL_DestroyTexture(tex);
}

int ButtonComponent::OneClick(bool* ifClicked)
{
	if (*ifClicked == true)
	{
		if (gamePlay::mainEvent.button.x >= mainRect.x && gamePlay::mainEvent.button.x <= mainRect.x + mainRect.w && gamePlay::mainEvent.button.y >= mainRect.y && gamePlay::mainEvent.button.y <= mainRect.y + mainRect.h)
		{
			*ifClicked = false;
			return 1;
		}
	}
	return 0;
}

int ButtonComponent::ClickInOut(bool* ifClicked)
{
	if (*ifClicked)
	{
		if (clicked == false && gamePlay::mainEvent.button.x >= mainRect.x && gamePlay::mainEvent.button.x <= mainRect.x + mainRect.w && gamePlay::mainEvent.button.y >= mainRect.y && gamePlay::mainEvent.button.y <= mainRect.y + mainRect.h)
		{
			clicked = true;
			*ifClicked = false;
			return 1;
		}
		else if (clicked == true && gamePlay::mainEvent.button.x >= mainRect.x && gamePlay::mainEvent.button.x <= mainRect.x + mainRect.w && gamePlay::mainEvent.button.y >= mainRect.y && gamePlay::mainEvent.button.y <= mainRect.y + mainRect.h)
		{
			*ifClicked = false;
			clicked = false;
			return 2;
		}
	}
	return 0;
}

void ButtonComponent::hover()
{
	if (gamePlay::mainEvent.button.x >= mainRect.x && gamePlay::mainEvent.button.x <= mainRect.x + mainRect.w && gamePlay::mainEvent.button.y >= mainRect.y && gamePlay::mainEvent.button.y <= mainRect.y + mainRect.h)
	{
		SDL_SetTextureColorMod(tex, 120, 120, 120);
	}
	else {
		SDL_SetTextureColorMod(tex, 170, 170, 170);
	}
}

bool ButtonComponent::render()
{
	textureMananger::Draw(tex, src, mainRect);

	if (gamePlay::mainEvent.button.x >= mainRect.x && gamePlay::mainEvent.button.x <= mainRect.x + mainRect.w && gamePlay::mainEvent.button.y >= mainRect.y && gamePlay::mainEvent.button.y <= mainRect.y + mainRect.h)
	{
		mainRect.w += 3;
		xChange += 3;
		mainRect.x--;
		if (mainRect.w == tempRect.w + 12)
		{
			mainRect.w -= 3;
			xChange -= 3;
			mainRect.x++;
		}

		mainRect.h += 3;
		yChange += 3;
		mainRect.y--;

		if (mainRect.h == tempRect.h + 12)
		{
			mainRect.h -= 3;
			yChange -= 3;
			mainRect.y++;
		}

		return true;
	}
	else if (mainRect.h > tempRect.h || mainRect.w > tempRect.w)
	{
		mainRect.h -= 3;
		mainRect.w -= 3;
		xChange -= 3;
		yChange -= 3;
		mainRect.x++;
		mainRect.y++;
	}
	return false;
}
