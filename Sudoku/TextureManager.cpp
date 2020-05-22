#include "TextureManager.h"

SDL_Texture* textureMananger::LoadTexture(const char* texture)
{
	SDL_Surface* Surface = NULL;

	Surface = IMG_Load(texture);
	if (Surface == NULL)
	{
		std::cout << "Error: Cannot find " << texture << ".png" << std::endl;
		SDL_Quit();
	}

	SDL_Texture* mainTexture = SDL_CreateTextureFromSurface(gamePlay::mainRen, Surface);
	SDL_FreeSurface(Surface);

	return mainTexture;
}

void textureMananger::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(gamePlay::mainRen, tex, &src, &dest);
}

SDL_Texture* textureMananger::loadTextureFromSprite(const char* textureName, SDL_Rect rect)
{
	SDL_Texture* source = textureMananger::LoadTexture(textureName);

	SDL_Texture* result = SDL_CreateTexture(gamePlay::mainRen, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
	SDL_SetRenderTarget(gamePlay::mainRen, result);
	SDL_RenderCopy(gamePlay::mainRen, source, &rect, NULL);
	SDL_SetRenderTarget(gamePlay::mainRen, NULL);
	SDL_RenderPresent(gamePlay::mainRen);
	return result;
}

void textureMananger::setIcon(const char* texture, SDL_Window* win)
{
	SDL_Surface* icon = NULL;
	icon = IMG_Load(texture);
	if (icon == NULL)
	{
		std::cout << "Error: Cannot find " << texture << std::endl;
	}
	SDL_SetWindowIcon(win, icon);
}


