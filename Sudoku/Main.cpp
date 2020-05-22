#include "Main.h"
#include "InputSystem.h"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Fonts.h"
#include "SudokuSolver.h"
#include "TextureManager.h"
#include "Button.h"

SDL_Renderer* gamePlay::mainRen;
SDL_Event gamePlay::mainEvent;

ButtonComponent* Startbutton;
ButtonComponent* quitButton;
ButtonComponent* restartButton;
ButtonComponent* AboutGameButton;
ButtonComponent* backButton;

int t[9][9];
int touchable[9][9];
int tempMap[9][9];

MouseHandler mouse;
MouseInputs m;
FontHolder* buttonFonts;

FontHolder fonts;
SudokuSolver sudokuSolver;

int** AnswerGrid;
#define SPACES "         "
SDL_Texture* backGround;
SDL_Texture* hover;
SDL_Texture* X;
SDL_Texture* pointSelect;

SDL_Rect pointer{ 192, 100, 64, 64 };
SDL_Rect src{ 0, 0, 32, 32 };

SDL_Rect cross{ 200, 700, 64, 64 };
SDL_Rect srcCross{ 0, 0, 64, 64 };

int rowActive = -1, colActive = -1;
int input = 3;
int cycle = 0;
int numTouch = -1;
int errors = 0;

InputSystem *IS;
bool a = false;
int inputAllowed;
int counter = 0;
int** tempsMap;

bool gamePlay::init(const char* title, int width, int height, int full)
{
	RenHeight = height;
	RenWidth = width;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failure in loading SDL:"<< SDL_GetError << std::endl;
		successfulInit = false;
		SDL_Quit();
		return successfulInit;
	}
	else
	{
		SDL_Init(SDL_INIT_VIDEO);

		int flag = 0;
		if (full)
		{
			flag = SDL_WINDOW_FULLSCREEN;
		}

		mainWin = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flag);
		mainRen = SDL_CreateRenderer(mainWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (mainRen == NULL || mainWin == NULL)
		{
			std::cout << "Failure in loading window" << std::endl;
			successfulInit = false;
			SDL_Quit();
			return successfulInit;
		}
		else
		{
			successfulInit = true;
		}
	}

	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		successfulInit = false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		successfulInit = false;
	}
	sudokuSolver.init();
	tempsMap = sudokuSolver.getGrid();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			t[i][j] = tempsMap[i][j];
			tempMap[i][j] = t[i][j];
		}
	}

	if (sudokuSolver.algorthim())
		sudokuSolver.printGrid();
	else
		std::cout << "no solution found" << std::endl;

	Startbutton = new ButtonComponent();
	Startbutton->init("Images/test.png", 360, 300, 256, 64);

	quitButton = new ButtonComponent();
	quitButton->init("Images/test.png", 420, 500, 128, 64);

	restartButton = new ButtonComponent();
	restartButton->init("Images/test.png", 360, 300, 256, 64);

	AboutGameButton = new ButtonComponent();
	AboutGameButton->init("Images/test.png", 360, 400, 256, 64);

	backButton = new ButtonComponent();
	backButton->init("Images/test.png", 50, 50, 64, 32);

	initSudoku();
	backGround = textureMananger::LoadTexture("Images/2.png");
	hover = textureMananger::LoadTexture("Images/1.png");
	X = textureMananger::LoadTexture("Images/x-mark-64.png");
	pointSelect = textureMananger::LoadTexture("Images/3.png");

	Running = successfulInit;
	return successfulInit;
}

bool gamePlay::initSudoku()
{
	AnswerGrid = sudokuSolver.getGrid();
	fonts.addFonts(83);
	int addOnX = 0;
	int addOnY = 0;

	std::stringstream num[81];

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fonts.loadF("TitilliumWeb-SemiBold.ttf", cycle, 212 + addOnY, 100 + addOnX, 32);
			num[cycle] << tempMap[j][i] << SPACES;
			std::string m_num(num[cycle].str());
			const char* send_num = m_num.c_str();
			fonts.setF(send_num, cycle, mainTextColor);

			if (tempMap[j][i] != 0) {
				touchable[j][i] = 0;
			}
			else if (tempMap[j][i] == 0) {
				touchable[j][i] = 1;
			}

			cycle++;
			addOnX += 64;
			if (j == 8) {
				addOnX = 0;
				addOnY += 64;
			}
		}
	}
	fonts.loadF("TitilliumWeb-SemiBold.ttf", 81, 400, 30, 48);
	fonts.setF("Sudoku", 81, mainTextColor);

	fonts.loadF("TitilliumWeb-SemiBold.ttf", 82, 50, 700, 48);
	fonts.setF("Errors:", 82, mainTextColor);

	buttonFonts = new FontHolder();
	buttonFonts->addFonts(9);
	buttonFonts->loadF("TitilliumWeb-SemiBold.ttf", 0, 435, 290, 48);
	buttonFonts->setF("Start", 0, mainTextColor);

	buttonFonts->loadF("TitilliumWeb-SemiBold.ttf", 1, 380, 130, 22);
	buttonFonts->setF("By Strahinja Marinkovic", 1, mainTextColor);

	buttonFonts->loadF("TitilliumWeb-SemiBold.ttf", 2, 450, 505, 32);
	buttonFonts->setF("Quit", 2, mainTextColor);

	buttonFonts->loadF("TitilliumWeb-SemiBold.ttf", 3, 310, 30, 48);
	buttonFonts->setF("Sorry... You Lost!", 3, mainTextColor);

	buttonFonts->loadF("TitilliumWeb-SemiBold.ttf", 4, 410, 290, 48);
	buttonFonts->setF("Restart", 4, mainTextColor);

	buttonFonts->loadF("TitilliumWeb-SemiBold.ttf", 5, 417, 390, 48);
	buttonFonts->setF("About", 5, mainTextColor);

	buttonFonts->loadF("TitilliumWeb-SemiBold.ttf", 6, 390, 130, 48);
	buttonFonts->setF("Good Job", 6, mainTextColor);

	buttonFonts->loadF("TitilliumWeb-SemiBold.ttf", 7, 40, 100, 22);
	buttonFonts->setF("This game was done by 5/4/2020, made by Strahinja Marinkovic in the 9th grade during coronavirus!", 7, mainTextColor);

	buttonFonts->loadF("TitilliumWeb-SemiBold.ttf", 8, 54, 50, 22);
	buttonFonts->setF("Quit", 8, mainTextColor);

	IS = new InputSystem();
	IS->addKey(9);
	IS->init();
	
	IS->setKey(Keys::ONE, 0);
	IS->setKey(Keys::TWO, 1);
	IS->setKey(Keys::THREE, 2);
	IS->setKey(Keys::FOUR, 3);
	IS->setKey(Keys::FIVE, 4);
	IS->setKey(Keys::SIX, 5);
	IS->setKey(Keys::SEVEN, 6);
	IS->setKey(Keys::EIGHT, 7);
	IS->setKey(Keys::NINE, 8);

	return true;
}

bool gamePlay::gameLoop()
{
	while (SDL_PollEvent(&mainEvent))
	{
		switch (mainEvent.type)
		{
			case SDL_QUIT:
			{
				Running = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				switch (mainEvent.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						Running = false;
						break;
					}
					if (inputAllowed && state == 1) {
					case SDLK_1:
					{
						input = 1;
						a = true;
						break;
					}
					case SDLK_2:
					{
						input = 2;
						a = true;
						break;
					}
					case SDLK_3:
					{
						input = 3;
						a = true;
						break;
					}
					case SDLK_4:
					{
						input = 4;
						a = true;
						break;
					}
					case SDLK_5:
					{
						input = 5;
						a = true;
						break;
					}
					case SDLK_6:
					{
						input = 6;
						a = true;
						break;
					}
					case SDLK_7:
					{
						input = 7;
						a = true;
						break;
					}
					case SDLK_8:
					{
						input = 8;
						a = true;
						break;
					}
					case SDLK_9:
					{
						input = 9;
						a = true;
						break;
					}
					}
				}
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				m.leftClick = mouse.LeftClick(mainEvent.button);
				m.rightClick = mouse.RightClick(mainEvent.button);
				break;
			}
		}
	}

	SDL_SetWindowResizable(mainWin, SDL_TRUE);

	return Running;
}

void gamePlay::cleanUp(gamePlay* game)
{
	SDL_DestroyWindow(mainWin);
	SDL_DestroyRenderer(mainRen);

	SDL_DestroyTexture(backGround);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(X);
	SDL_DestroyTexture(pointSelect);

	IS->destroy();

	delete buttonFonts;
	delete Startbutton;
	delete quitButton;
	delete restartButton;
	delete AboutGameButton;
	delete backButton;
	delete IS;

	SDL_Quit();
}

void gamePlay::update()
{
	if (state == 0)
	{
		Startbutton->hover();
		if (Startbutton->OneClick(&m.leftClick) == 1)
		{
			state = 1;
		}
		quitButton->hover();
		if (quitButton->OneClick(&m.leftClick) == 1)
		{
			Running = false;
		}
	}
	if (state == 1)
	{
		pointer.x = 192;
		pointer.y = 100;
		if (m.leftClick)
		{
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (mainEvent.button.x >= pointer.x && mainEvent.button.x <= pointer.x + pointer.w && mainEvent.button.y >= pointer.y && mainEvent.button.y <= pointer.y + pointer.h)
					{
						rowActive = i;
						colActive = j;
						numTouch = tempMap[i][j];
						std::cout << numTouch;
						if (touchable[j][i] == 1) {
							inputAllowed = 1;
						}
						else
							input = NULL;
					}
					else
						input = NULL;

					pointer.x += 64;
					if (j == 8) {
						pointer.y += 64;
						pointer.x = 192;
					}
				}
				m.leftClick = false;
			}
		}

		cycle = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (touchable[j][i] == 1) {
					if (rowActive == j && colActive == i) {
						if (a == true && input != NULL) {
							std::stringstream num;
							num << input;
							std::string m_num(num.str());
							const char* send_num = m_num.c_str();
							if (input != AnswerGrid[j][i]) {
								errors++;
								fonts.setF(send_num, cycle, wrong);
								tempMap[j][i] = input;
							}
							else {
								fonts.setF(send_num, cycle, changer);
								tempMap[j][i] = input;
							}
							a = false;
						}
					}
				}
				cycle++;
			}
		}

		counter = -1;

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				counter++;
				if (tempMap[j][i] == 0) {
					break;
				}
				if (counter == 80)
					state = 3;
			}
		}

		if (errors == 5)
			state = 2;
	}
	if (state == 2)
	{
		quitButton->hover();
		if (quitButton->OneClick(&m.leftClick) == 1)
		{
			Running = false;
		}
		restartButton->hover();
		if (restartButton->OneClick(&m.leftClick) == 1)
		{
			state = 1;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					tempMap[i][j] = t[i][j];
				}
			}
			errors = 0;
		}
		AboutGameButton->hover();
		if (AboutGameButton->OneClick(&m.leftClick) == 1)
		{
			state = 4;
		}
	}
	if (state == 3)
	{
		quitButton->hover();
		if (quitButton->OneClick(&m.leftClick) == 1)
		{
			Running = false;
		}
		AboutGameButton->hover();
		if (AboutGameButton->OneClick(&m.leftClick) == 1)
		{
			state = 4;
		}
	}
	if (state == 4)
	{
		backButton->hover();
		if (backButton->OneClick(&m.leftClick) == 1)
		{
			Running = false;
		}
	}
}
void gamePlay::render()
{
	SDL_RenderClear(mainRen);
	SDL_SetRenderDrawColor(mainRen, 200, 200, 200, 100);

	if (state == 0)
	{
		fonts.renderF(81);
		Startbutton->render();
		quitButton->render();
		buttonFonts->renderF(0);
		buttonFonts->renderF(1);
		buttonFonts->renderF(2);
	}

	if (state == 1)
	{
		pointer.x = 192;
		pointer.y = 100;

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (rowActive == i || colActive == j)
					textureMananger::Draw(hover, src, pointer);
				else
					textureMananger::Draw(backGround, src, pointer);			
				if (rowActive == i && colActive == j) {				
					textureMananger::Draw(pointSelect, src, pointer);
				}
				if (tempMap[i][j] == numTouch && numTouch != 0)
					textureMananger::Draw(hover, src, pointer);
				if (j == 2 || j == 5) {
					pointer.x += 3;
				}
				pointer.x += 64;
				if (j == 8) {
					pointer.y += 64;
					pointer.x = 192;
					if (i == 2 || i == 5)
						pointer.y += 3;
				}
			}
		}

		cycle = 0;

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (tempMap[j][i] != 0)
					fonts.renderF(cycle);
				cycle++;
			}
		}

		cross.x = 200;
		cross.y = 700;
		for (int i = 0; i < errors; i++) {
			textureMananger::Draw(X, srcCross, cross);
			cross.x += 70;
		}

		fonts.renderF(81);
		fonts.renderF(82);
	}
	if (state == 2)
	{
		buttonFonts->renderF(3);
		quitButton->render();
		restartButton->render();
		AboutGameButton->render();
		buttonFonts->renderF(2);
		buttonFonts->renderF(4);
		buttonFonts->renderF(5);
	}
	if (state == 3)
	{
		buttonFonts->renderF(6);
		quitButton->render();
		buttonFonts->renderF(2);
		AboutGameButton->render();
		buttonFonts->renderF(5);
	}
	if (state == 4)
	{
		buttonFonts->renderF(7);
		backButton->render();
		buttonFonts->renderF(8);
	}
	SDL_RenderPresent(mainRen);
}