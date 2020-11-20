#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Stuff.hpp"

Vector2f::Vector2f()
:x(0.0f), y(0.0f){}

Vector2f::Vector2f(float p_x, float p_y)	
:x(p_x), y(p_y){}

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
