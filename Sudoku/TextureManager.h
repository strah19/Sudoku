#pragma once

#include "Main.h"

class textureMananger
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static SDL_Texture* loadTextureFromSprite(const char* filename, SDL_Rect rect);
	static void setIcon(const char* tex, SDL_Window* win);
};
