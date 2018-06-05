#include "Render.h"
#include <string>


/*
Render.cpp

file contains variables related to the game window/renderer.  functions all utilize SDL, and either create the game window, or deal with creating the view in the window.  
*/

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;
static bool created = false;
static SDL_Texture* zero;
static SDL_Texture* one;
static SDL_Texture* two;
static SDL_Texture* three;
static SDL_Texture* four;
static SDL_Texture* five;
static SDL_Texture* six;
static SDL_Texture* seven;
static SDL_Texture* eight;
static SDL_Texture* nine;


void create()//initialization. Initializes SDL, creates an SDL window and renderer.
{
	if (created) return; //leave function if the created function has already been called.
 	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "Could not initialize SDL error." << std::endl;
		return;
	}

	window = SDL_CreateWindow("Pentris - The Pentomino Puzzle Game", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		SDLlogError("SDL_CreateWindow");
		SDL_Quit();
		return;
	}


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		SDLlogError("SDL_CreateRenderer");
		SDL_Quit();
		return;
	}
	created = true;


	zero = createTexture("images/zero.png");
	one = createTexture("images/one.png");
	two = createTexture("images/two.png");
	three = createTexture("images/three.png");
	four = createTexture("images/four.png");
	five = createTexture("images/five.png");
	six = createTexture("images/six.png");
	seven = createTexture("images/seven.png");
	eight = createTexture("images/eight.png");
	nine = createTexture("images/nine.png");
}


//creates an SDL_Texture for use with SDL_Renderer
SDL_Texture* createTexture(std::string filename)
{
	if (!created)
	{
		create();
	}
	SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());
	if (texture == nullptr)
	{
		SDLlogError("IMG_LoadTexture");
	}
	return texture;
}

//Adds texture to the renderer state, at specified coordinates.
void renderTexture(SDL_Texture *tex, int x, int y) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, tex, NULL, &rect);
}

//draws everything in the current render state to screen, then clears the render state for the next frame.
void draw()
{
	if (created)
	{
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	}
}

//renders numbers. takes in the number, the number of digits to render, and the x,y to render the number at.
void renderNumber(int numToRender, int numDigits, int x, int y)
{
	if (!created) create();
	int width = 17; //horizontal number of pixels between each digit
	int currentX = x + width * (numDigits-1);
	while (numToRender > 0 && numDigits-- > 0)
	{
		int digit = numToRender % 10;
		renderTexture(digitLookup(digit), currentX, y);
		currentX -= width;
		numToRender = numToRender / 10;
	}
	while (numDigits-- > 0)
	{
		renderTexture(digitLookup(0), currentX, y);
		currentX -= width;
		numToRender = numToRender / 10;
	}
}

//returns file location for image corresponding digit
SDL_Texture* digitLookup(int digit)
{
	switch (digit)
	{
	case 0:
		return zero;
		break;
	case 1:
		return one;
		break;
	case 2:
		return two;
		break;
	case 3:
		return three;
		break;
	case 4:
		return four;
		break;
	case 5:
		return five;
		break;
	case 6:
		return six;
		break;
	case 7:
		return seven;
		break;
	case 8:
		return eight;
		break;
	case 9:
		return nine;
		break;
	}
	return zero;
}

//prints SDL errors to the console
void SDLlogError(const std::string &msg)
{
	std::cout << msg << " error: " << SDL_GetError() << std::endl;
}