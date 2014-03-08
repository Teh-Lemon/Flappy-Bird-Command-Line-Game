#ifndef PLAYER
#define PLAYER

#include "ConsoleUtils.h"

class Player
{

private:
	// Vertical location on the stage
	int positionY;
	// Vertical velocity of the player from the bottom
	int velocityY;
	// Is the player dead or not
	bool isAlive;
	// Player model
	char playerShape;
	// Text Color
	WORD TextColor;


	void ApplyGravity();
	// Cap the velocity
	void ApplySpeedLimits();


public:
	Player(void);
	~Player(void);

	void Flap();

	void Update();

	// Getters
	int GetPositionY();
	bool GetIsAlive();
	char GetPlayerShape();
	WORD GetTextColor();

	// Setters
	void SetPositionY(int);
	void SetIsAlive(bool);
	void SetPlayerShape(char);
	void SetVelocityY(int);
	void SetTextColor(WORD);
};

#endif

