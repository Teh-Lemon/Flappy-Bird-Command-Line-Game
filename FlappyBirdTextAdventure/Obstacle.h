#ifndef OBSTACLE
#define OBSTACLE

class Obstacle
{
private:
	int height;
	int width;
	int positionX;
	char shape;

public:
	Obstacle(void);
	~Obstacle(void);

	// Getters
	int GetHeight();
	int GetWidth();
	int GetPositionX();
	char GetShape();
};

#endif

