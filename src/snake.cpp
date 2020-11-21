#include "Utils.hpp"
#include "Snake.hpp"

Snake::Snake(Vector2f p_pos)
:pos(p_pos){}

void Snake::setDir(Direction p_dir)
{
	dir = p_dir;
}

void Snake::setPos(Vector2f p_pos)
{
	pos = p_pos;
}
