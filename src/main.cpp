#include <SDL2/SDl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <vector>
#include <string>

#include "Snake.hpp"
#include "Utils.hpp"
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
		return 1;
	}

	if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) != 0)
    {
    	std::cout << "Mix_OpenAudio failed. Error Code: " << SDL_GetError() << std::endl;
        return 1;
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

	Snake snake(Vector2f(windowWidth/2, windowHeight/2));

	SDL_Texture* snakeTex = loadTexture("res/gfx/snakeTex.png", renderer);
	SDL_Texture* fruitTex = loadTexture("res/gfx/fruitTex.png", renderer);

	Mix_Chunk* munch = loadSoundEffect("res/dev/munch.mp3");

	SDL_Texture* winText = loadText(renderer, "res/dev/Flix-Normal.ttf", "You Win!", {0, 0, 0}, 70);
	SDL_Texture* loseText = loadText(renderer, "res/dev/Flix-Normal.ttf", "You Lose.", {0, 0, 0}, 70);

	
	std::vector<Fruit> fruits;
	int frameCount = 0;
	int timeCount = 0;
	int score = 0;
	bool gameRunning  = true;
	SDL_Event event;
	bool gameEnded = false;

	while (gameRunning)
	{
		if (gameEnded)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						gameRunning = false;
						break;
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE)
							gameRunning = false;
						break;
				}
			}

			SDL_RenderClear(renderer);

			SDL_Texture* scoreText;

			char result[100]; // Depressing C string stuff
			strcpy(result, "You Scored: "); // Some more of that
			strcat(result, std::to_string(score).c_str()); // This just doesn't end, does it?
			std::cout << result << std::endl;
			int x, y;

			if (score > 7)
			{
				SDL_QueryTexture(winText, NULL, NULL, &x, &y);
				render(renderer, winText, Vector2f(windowWidth/2 - x/2, windowHeight/2 - y), Vector2f(x, y));
			}else
			{
				SDL_QueryTexture(loseText, NULL, NULL, &x, &y);
				render(renderer, loseText, Vector2f(windowWidth/2 - x/2, windowHeight/2 - y), Vector2f(x, y));	
			}

			scoreText = loadText(renderer, "res/dev/Flix-Normal.ttf", result, {0, 0, 0}, 50);
			std::cout << "Passed the text formation\n";
			SDL_QueryTexture(scoreText, NULL, NULL, &x, &y);
			std::cout << "Passed Query\n";
			render(renderer, scoreText, Vector2f(windowWidth/2 - x/2, windowHeight/2), Vector2f(x, y));
			std::cout << "Passed rendering\n";

			SDL_RenderPresent(renderer);
			SDL_DestroyTexture(scoreText);
			std::cout << "Destroyed\n";
		}else
		{
			frameCount++;
			timeCount++;
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
			else if (snake.getPos().getX() + size > windowWidth)
				snake.setPos(Vector2f(0, snake.getPos().getY()));

			if (snake.getPos().getY() < 0)
				snake.setPos(Vector2f(snake.getPos().getX(), windowHeight-size));
			else if (snake.getPos().getY() + size > windowHeight)
				snake.setPos(Vector2f(snake.getPos().getX(), 0));

			SDL_RenderClear(renderer);

			if (frameCount >= 300)
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
				{
					fruits.erase(fruits.begin() + i);
					score++;
					Mix_PlayChannel(-1, munch, 0);
				}



				render(renderer, fruitTex, fruits[i].getPos(), Vector2f(size, size));
			} 

			if (timeCount == 2000)
				gameEnded = true;


			render(renderer, snakeTex, snake.getPos(), Vector2f(size, size));
			SDL_RenderPresent(renderer);
			std::cout << timeCount << std::endl;
		}
	}
	
	Mix_FreeChunk(munch);
	SDL_DestroyTexture(fruitTex);
	SDL_DestroyTexture(snakeTex);
	SDL_DestroyTexture(winText);
	SDL_DestroyTexture(loseText);

	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}
