#include <SDL2/SDl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Snake.hpp"
#include <Stuff.hpp>


void render(SDL_Renderer* p_renderer, SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size);
SDL_Texture* loadTexture(const char* p_filePath, SDL_Renderer* renderer);


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
	const int size = 20;
	const int d = 5;

	SDL_Window* window = NULL;
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window Initialization Failed. Error Code: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);

	if (renderer == NULL)
	{
		std::cout << "Renderer Initialization Failed. Error Code: " << SDL_GetError() << std::endl;
		return 1;
	}
	Snake snake;
	SDL_Texture* snakeTex = loadTexture("res/gfx/snakeTex.png", renderer);

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
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							gameRunning = false;
							break;
						case SDLK_RIGHT:
							if (snake.getDir() != LEFT)
								snake.setDir(RIGHT);
							break;
						case SDLK_d:
							if (snake.getDir() != LEFT)
								snake.setDir(RIGHT);
							break;
						case SDLK_LEFT:
							if (snake.getDir() != RIGHT)
								snake.setDir(LEFT);
							break;
						case SDLK_a:
							if (snake.getDir() != RIGHT)
								snake.setDir(LEFT);
							break;
						case SDLK_DOWN:
							if (snake.getDir() != UP)
								snake.setDir(DOWN);
							break;
						case SDLK_s:
							if (snake.getDir() != UP)
								snake.setDir(DOWN);
							break;
						case SDLK_UP:
							if (snake.getDir() != DOWN)
								snake.setDir(UP);
							break;
						case SDLK_w:
							if (snake.getDir() != DOWN)
								snake.setDir(UP);
							break;					
					}
			}
		}

		switch (snake.getDir())
		{
			case RIGHT:
				snake.setPos(Vector2f(snake.getPos().getX()+d, snake.getPos().getY()));
				break;
			case LEFT:
				snake.setPos(Vector2f(snake.getPos().getX()-d, snake.getPos().getY()));
				break;
			case UP:
				snake.setPos(Vector2f(snake.getPos().getX(), snake.getPos().getY()-d));
				break;
			case DOWN:
				snake.setPos(Vector2f(snake.getPos().getX(), snake.getPos().getY()+d));
				break;
			default:
				std::cout << "GIMME DIR\n";
		}
		if (snake.getPos().getX() < 0)
			snake.setPos(Vector2f(windowWidth - size, snake.getPos().getY()));
		else if (snake.getPos().getX() >= windowWidth)
			snake.setPos(Vector2f(0, snake.getPos().getY()));

		if (snake.getPos().getY() < 0)
			snake.setPos(Vector2f(snake.getPos().getX(), windowHeight-size));
		else if (snake.getPos().getY() >= windowHeight)
			snake.setPos(Vector2f(snake.getPos().getX(), 0));

		SDL_RenderClear(renderer);
		render(renderer, snakeTex, snake.getPos(), Vector2f(size, size));
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(snakeTex);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void render(SDL_Renderer* p_renderer, SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size)
{
	SDL_Rect dst;
	dst.x = p_pos.getX();
	dst.y = p_pos.getY();
	dst.w = p_size.getX();
	dst.h = p_size.getY();

	SDL_RenderCopy(p_renderer, p_tex, NULL, &dst);
}

SDL_Texture* loadTexture(const char* p_filePath, SDL_Renderer* renderer)
{
	
	SDL_Texture* texture = NULL;

	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
	{ 
		std::cout << "FAILED TO LOAD TEXTURES. PLEASE INFORM DEVS. ERROR: " << SDL_GetError() << std::endl;
	}

	return texture;
}
