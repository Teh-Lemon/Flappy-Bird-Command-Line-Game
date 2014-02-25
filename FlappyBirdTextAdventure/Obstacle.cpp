#include "Obstacle.h"

const int GAP_SIZE = 3;

Obstacle::Obstacle(int setHeight, int spawnPos)
	: height(setHeight), positionX(spawnPos)
{
	width = 1;
	shape = '|';
	velocityX = -1;
}


Obstacle::~Obstacle(void)
{
}

// Getters
int Obstacle::GetHeight()
{
	return height;
}
void Obstacle::SetHeight(int newHeight)
{
	height = newHeight;
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

int Obstacle::GetGapSize()
{
	return GAP_SIZE;
}

void Obstacle::Update()
{
	positionX += velocityX;
}
