#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

void create();
SDL_Texture* createTexture(std::string filename);
void renderTexture(SDL_Texture *tex, int x, int y);
void SDLlogError(const std::string &msg);
void updateScreen();