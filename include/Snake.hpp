#pragma once
#include "Utils.hpp"

class Snake
{
	public:
		Snake(Vector2f p_pos);
		void setDir(Direction p_dir);
		Vector2f getPos(){return pos;}
		Direction getDir(){return dir;}
		void setPos(Vector2f p_pos);

	private:
		Direction dir;
		Vector2f pos;
		int length = 1;
};
