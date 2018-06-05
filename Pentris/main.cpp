#include <SDL.h>
#include "render.h"
#include "game.h"

/*
main.cpp

file contains main function, which serves as a basic loop running the game at ~60hz ticks.
*/

static bool keepGoing = true;
static void eventHandler();

int main(int argc, char *argv[])
{
	Uint32 lastTick = 0;
	Uint32 currentTick = SDL_GetTicks();
	create();
	while (keepGoing)
	{
		do // checks if ~1/60 second has passed since last tick loop
		{
			currentTick = SDL_GetTicks();
		} while (currentTick - lastTick < 16);
		lastTick = currentTick;
		eventHandler();
		gameStateUpdate();
		renderBoard();
		draw();
		if (isGameOver()) keepGoing = false;
	}
	clearGame();
	SDL_Quit();
	return 0;
}

//called every tick, handles any events which occured since last call
void eventHandler()
{

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			keepGoing = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			readKeyInput(event.key.keysym.sym);
		}

	}
}

