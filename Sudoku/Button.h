#pragma once

#include "main.h"
#include "TextureManager.h"

class ButtonComponent
{
public:
	~ButtonComponent();

	bool init(const char* text, int x, int y, int w, int h);
	int OneClick(bool* ifClicked);
	int ClickInOut(bool* ifClicked);
	void hover();
	bool render();
	inline SDL_Texture* getTex() { return tex; }
	inline SDL_Rect getSrc() { return src; }
	inline SDL_Rect getMain() { return mainRect; }
private:
	bool clicked = false;
	int xChange = 0;
	int yChange = 0;
	int flag = 1;
	SDL_Rect tempRect;
	SDL_Rect mainRect;
	SDL_Rect src;
	SDL_Texture* tex;
};



