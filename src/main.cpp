#include <SDL2/SDl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

#include "Snake.hpp"
#include "Stuff.hpp"
#include "Fruit.hpp"

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
	SDL_Texture* fruitTex = loadTexture("res/gfx/fruitTex.png", renderer);
	std::vector<Fruit> fruits;
	int frameCount = 0;

	bool gameRunning  = true;
	SDL_Event event;

	while (gameRunning)
	{
		frameCount++;
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

		if (frameCount >= 250)
		{
			frameCount = 0;
			fruits.push_back(Fruit(Vector2f(rand() % windowWidth, rand() % windowHeight)));
		}

		for (unsigned i = 0; i < fruits.size(); i++)
		{
			fruits[i].timeAlive--;
			if (fruits[i].timeAlive <= 0)
				fruits.erase(fruits.begin() + i);

			if (snake.getPos().getX() + size > fruits[i].getPos().getX() && snake.getPos().getX() < fruits[i].getPos().getX() + size && snake.getPos().getY() + size > fruits[i].getPos().getY() && snake.getPos().getY() < fruits[i].getPos().getY() + size)
				fruits.erase(fruits.begin() + i);

			render(renderer, fruitTex, fruits[i].getPos(), Vector2f(size, size));
		} 


		render(renderer, snakeTex, snake.getPos(), Vector2f(size, size));
		SDL_RenderPresent(renderer);
		std::cout << frameCount << std::endl;
	}

	SDL_DestroyTexture(snakeTex);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
