#pragma once

#include <SDL2/SDl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

enum Direction {UP, DOWN, LEFT, RIGHT};

class Vector2f
{
	private:
		float x, y;

	public:
		float getX(){return x;}
		float getY(){return y;}
		Vector2f();
		Vector2f(float p_x, float p_y);
};

void render(SDL_Renderer* p_renderer, SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size);

SDL_Texture* loadTexture(const char* p_filePath, SDL_Renderer* renderer);

Mix_Chunk* loadSoundEffect(const char* p_filePath);