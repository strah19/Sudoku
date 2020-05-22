#pragma once

#include "Main.h"
#include <string.h>

class FontManager;

class FontHolder
{
public:
	FontHolder();
	~FontHolder();
	bool loadF(const char* name, int ID, int x, int y, int size);
	void setF(const char* text, int ID, SDL_Color c);
	void renderF(int ID);
	void addFonts(int num);
private:
	int numFont;
	static const int maxFonts = 10;

	FontManager* m_font[maxFonts];
};

class FontManager
{
public:
	~FontManager();
	bool loadFont(const char* name, int size);
	void setFont(const char* text, SDL_Color c);
	void render();
	void setPosition(int x, int y);
private:
	TTF_Font* font;
	const char* fontName;

	SDL_Rect fontRect;
	SDL_Texture* fontTexture;
	int Width, Height;

	friend class FontHolder;
	FontHolder* parentFont;

	int ID;
};
