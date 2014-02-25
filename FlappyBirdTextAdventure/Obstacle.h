#ifndef OBSTACLE
#define OBSTACLE

class Obstacle
{
private:
	int height;
	int width;
	int positionX;
	int velocityX;
	char shape;

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

	// Setters
	void SetHeight(int);
};

#endif

