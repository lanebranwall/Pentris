//Handles SDL Rendering

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_Handler.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
bool created = false;


void create() //initialization creates SDL window and SDL renderer
{
	if (created) return;//will not run if already created

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "Could not initialize SDL error." << std::endl;
		return;
	}


	window = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
}

//creates an SDL_Texture for rendering 
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

//Queries an SDL_Texture and prepares it to be drawn.
void renderTexture(SDL_Texture *tex, int x, int y) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, tex, NULL, &rect);
}

void draw()
{
	SDL_RenderPresent(renderer);
}

//prints SDL_errors to console
void SDLlogError(const std::string &msg)
{
	std::cout << msg << " error: " << SDL_GetError() << std::endl;
}