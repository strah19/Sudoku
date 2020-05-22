#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <string>
#include <sstream>
#include <random>

namespace Keys
{
	enum listOfKeys {ONE = SDL_SCANCODE_1
    ,TWO = SDL_SCANCODE_2
	, THREE = SDL_SCANCODE_3
	, FOUR = SDL_SCANCODE_4
	, FIVE = SDL_SCANCODE_5
	, SIX = SDL_SCANCODE_6
	, SEVEN = SDL_SCANCODE_7
	, EIGHT = SDL_SCANCODE_8
	, NINE = SDL_SCANCODE_9
	};
}

struct MouseInputs
{
	bool leftClick;
	bool rightClick;
	bool UpScroll;
	bool DownScroll;
};

class gamePlay
{
private:
	SDL_Window* mainWin;
	bool Running;
	bool successfulInit;
	int RenWidth, RenHeight;
	int state = 0;
	int fps;
public:
	bool init(const char* title, int width, int height, int full);
	void cleanUp(gamePlay*);
	bool initSudoku();
	bool gameLoop();
	void render();
	void update();

    static SDL_Renderer* mainRen;
	static SDL_Event mainEvent;
	SDL_Color mainTextColor = { 0, 0, 0, 0 };
	SDL_Color changer = { 100, 100, 100, 255 };
	SDL_Color wrong = { 255, 0, 0, 255 };

	inline void getFPS(int f) { fps = f; }
	inline bool getDone() const { return Running; }
};

