#include "Obstacle.h"

const int GAP_SIZE = 3;

Obstacle::Obstacle(int setHeight, int spawnPos)
	: height(setHeight), positionX(spawnPos)
{
	width = 1;
	shape = '|';
	velocityX = -1;
	TextColor = FOREGROUND_GREEN|FOREGROUND_INTENSITY;
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

// TextColor getter/setter
WORD Obstacle::GetTextColor()
{
	return TextColor;
}

void Obstacle::SetTextColor(WORD newColor)
{
	TextColor = newColor;
}

void Obstacle::Update()
{
	positionX += velocityX;
}
