#include "Fonts.h"

FontHolder::FontHolder()
{
	numFont = 0;
}

void FontHolder::addFonts(int num)
{
	numFont = num;
	for (int i = 0; i < numFont; i++)
	{
		m_font[i] = new FontManager;
		m_font[i]->parentFont = this;
		m_font[i]->ID = i;
	}
}

FontHolder::~FontHolder()
{
	for (int i = 0; i < numFont; i++)
	{
		delete m_font[i];
	}
}

bool FontHolder::loadF(const char* name, int ID, int x, int y, int size)
{
	for (int i = 0; i < numFont; i++)
	{
		if (ID == m_font[i]->ID)
		{
			m_font[i]->setPosition(x, y);
			return m_font[i]->loadFont(name, size);
		}
	}
}

void FontHolder::setF(const char* text, int ID, SDL_Color c)
{
	for (int i = 0; i < numFont; i++)
	{
		if (ID == m_font[i]->ID)
		{
			m_font[i]->setFont(text, c);
		}
	}
}

void FontHolder::renderF(int ID)
{
	for (int i = 0; i < numFont; i++)
	{
		if (ID == m_font[i]->ID)
		{
			m_font[i]->render();
		}
	}
}
void FontManager::setPosition(int x, int y)
{
	fontRect.x = x;
	fontRect.y = y;
}

FontManager::~FontManager()
{
	TTF_CloseFont(font);
}

bool FontManager::loadFont(const char* name, int size)
{
	fontName = name;
	font = TTF_OpenFont(name, size);
	if (!font)
	{
		std::cout << "Cannot find:" << name << std::endl;
		SDL_Quit();
		return false;
	}

	return true;
}

void FontManager::setFont(const char* text, SDL_Color c)
{
	SDL_DestroyTexture(fontTexture);

	SDL_Color color = c;

	SDL_Surface* fontSurface = TTF_RenderText_Blended(font, text, color);
	Width = fontSurface->w;
	Height = fontSurface->h;

	fontRect.w = Width;
	fontRect.h = Height;

	fontTexture = SDL_CreateTextureFromSurface(gamePlay::mainRen, fontSurface);

	SDL_FreeSurface(fontSurface);
}

void FontManager::render()
{
	SDL_RenderCopy(gamePlay::mainRen, fontTexture, NULL, &fontRect);
}
