#include "Obstacle.h"


Obstacle::Obstacle(void)
{
	height = 1;
	width = 1;
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
