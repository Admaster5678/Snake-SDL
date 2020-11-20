#pragma once
#include <SDL2/SDL.h>
#include <Stuff.hpp>

class Snake
{
public:
	Snake();
	void setDir(Direction p_dir);
	Vector2f getPos(){return pos;}
	Direction getDir(){return dir;}
	void setPos(Vector2f p_pos);

private:
	Direction dir;
	Vector2f pos;
	int length = 1;
};
