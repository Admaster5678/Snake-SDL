#include "Snake.hpp"

Snake::Snake()
{
	pos = Vector2f(300, 350);
}

void Snake::setDir(Direction p_dir)
{
	dir = p_dir;
}

void Snake::setPos(Vector2f p_pos)
{
	pos = p_pos;
}