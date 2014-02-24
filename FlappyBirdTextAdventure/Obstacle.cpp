#include "Obstacle.h"


Obstacle::Obstacle(void)
{
	height = 5;
	width = 5;
	shape = '|';
	positionX = 5;
}


Obstacle::~Obstacle(void)
{
}

// Getters
int Obstacle::GetHeight()
{
	return height;
}
int Obstacle::GetWidth()
{
	return width;
}
int Obstacle::GetPositionX()
{
	return positionX;
}
char Obstacle::GetShape()
{
	return shape;
}
