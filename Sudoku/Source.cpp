#include "Main.h"

gamePlay* game = nullptr;

int main(int argc, char* argv[])
{
	const int fps = 60;
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	game = new gamePlay;
	game->init("Sudoku", 1000, 800, 0);

	while (game->getDone())
	{
		frameStart = SDL_GetTicks();

		game->gameLoop();

		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		game->getFPS(frameTime);

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->cleanUp(game);

	return 0;
	return 0;
}