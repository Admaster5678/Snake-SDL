#include <SDL2/SDl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		std::cout << "SDL_Init Failed. Error Code: " << SDL_GetError() << std::endl;

	return 0;
}