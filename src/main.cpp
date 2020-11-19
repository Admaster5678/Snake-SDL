#include <SDL2/SDl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Snake.hpp"
#include <Stuff.hpp>

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Failed. Error Code: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "IMG_Init Failed. Error Code: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init failed. Error Code: " << SDL_GetError() << std::endl;
	}

	const int windowWidth = 600;
	const int windowHeight = 700;

	SDL_Window* window = NULL;
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window Initialization Failed. Error Code: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);

	if (renderer == NULL)
	{
		std::cout << "Renderer Initialization Failed. Error Code: " << SDL_GetError() << std::endl;
		return 1;
	}
	Snake snake();

	bool gameRunning  = true;
	SDL_Event event;

	while (gameRunning)
	{
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					gameRunning = false;
					break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}