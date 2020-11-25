#include <SDL2/SDl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Utils.hpp"

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

SDL_Texture* loadTexture(const char* p_filePath, SDL_Renderer* p_renderer)
{
	SDL_Texture* texture = NULL;

	texture = IMG_LoadTexture(p_renderer, p_filePath);

	if (texture == NULL)
	{ 
		std::cout << "FAILED TO LOAD TEXTURES. PLEASE INFORM DEVS. ERROR: " << SDL_GetError() << std::endl;
	}

	return texture;
}

Mix_Chunk* loadSoundEffect(const char* p_filePath)
{
	Mix_Chunk* sound = NULL;
	sound = Mix_LoadWAV(p_filePath);

	if (sound == NULL)
		std::cout << "FAILED TO LOAD SOUNDS. PLEASE INFORM DEVS. ERROR: " << SDL_GetError() << std::endl;

	return sound;
}

SDL_Texture* loadText(SDL_Renderer* p_renderer, const char* p_filePath, const char p_text[], SDL_Color p_color, int p_size)
{
	TTF_Font* font = NULL;
	font = TTF_OpenFont(p_filePath, p_size);

	if (font == NULL)
		std::cout << "FAILED TO LOAD FONT. PLEASE INFORM DEVS. ERROR: " << SDL_GetError() << std::endl;

	SDL_Surface* textSurface = NULL;
	textSurface = TTF_RenderText_Blended(font, p_text, p_color);
	if (textSurface == NULL)
		std::cout << "Cannot create textSurface from font. Error Code: " << SDL_GetError() << std::endl;

	TTF_CloseFont(font);

	SDL_Texture* text = NULL;
	text = SDL_CreateTextureFromSurface(p_renderer, textSurface);
	if (textSurface == NULL)
	{
		std::cout << "Cannot create fontTexture. Error Code: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(textSurface);

	return text;
}
