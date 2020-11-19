#pragma once

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