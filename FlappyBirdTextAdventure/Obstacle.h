#ifndef OBSTACLE
#define OBSTACLE

#include "ConsoleUtils.h"

class Obstacle
{
private:
	int height;
	int width;
	int positionX;
	int velocityX;
	char shape;	
	// Text Color
	WORD TextColor;

public:
	Obstacle(int, int);
	~Obstacle(void);

	void Update();

	// Getters
	int GetHeight();
	int GetWidth();
	int GetPositionX();
	char GetShape();
	int GetGapSize();	
	WORD GetTextColor();

	// Setters
	void SetHeight(int);	
	void SetTextColor(WORD);
};

#endif

