#include "Player.h"

const int GRAVITY = 1;
const int MAX_VELOCITY_Y = 3;
const int MIN_VELOCITY_Y = -1;
const int JUMP_VELOCITY = 3;

Player::Player(void)
{
	// Player defaults
	positionY = 5;
	playerShape = 'w';
	velocityY = 0;
	isAlive = true;
}

Player::~Player(void)
{
}

// Position getter/setter
int Player::GetPositionY()
{
	return positionY;
}

void Player::SetPositionY(int newLocation)
{
	positionY = newLocation;
}

// IsDead getter/setter
bool Player::GetIsAlive()
{
	return isAlive;
}

void Player::SetIsAlive(bool newIsAlive)
{
	isAlive = newIsAlive;
}

// Player shape getter/setter
char Player::GetPlayerShape()
{
	return playerShape;
}

void Player::SetPlayerShape(char newShape)
{
	playerShape = newShape;
}

// Velocity Y getter/setter
void Player::SetVelocityY(int newVel)
{
	velocityY = newVel;
}

void Player::ApplyGravity()
{
	velocityY -= GRAVITY;
}

void Player::ApplySpeedLimits()
{
	if (velocityY < MIN_VELOCITY_Y)
	{
		velocityY = MIN_VELOCITY_Y;
	}
	else if (velocityY > MAX_VELOCITY_Y)
	{
		velocityY = MAX_VELOCITY_Y;
	}
}

void Player::Flap()
{
	velocityY = JUMP_VELOCITY;
}

void Player::Update()
{
	ApplyGravity();
	ApplySpeedLimits();

	// Draw from the top of the screen
	positionY -= velocityY;
}