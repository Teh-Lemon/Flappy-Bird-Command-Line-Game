#ifndef PLAYER
#define PLAYER

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

	// Setters
	void SetPositionY(int);
	void SetIsAlive(bool);
	void SetPlayerShape(char);
	void SetVelocityY(int);
};

#endif

