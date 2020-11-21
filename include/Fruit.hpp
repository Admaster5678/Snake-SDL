#pragma once
#include "Utils.hpp"

class Fruit
{
	public:
		Fruit(Vector2f p_pos)
		:pos(p_pos){}
		Vector2f getPos(){return pos;}
		int timeAlive = 700;

	private:
		Vector2f pos;
};