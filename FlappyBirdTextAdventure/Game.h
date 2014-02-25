#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Player.h"
#include "Verb.h"
#include "Obstacle.h"

class Game
{
private:
	// Player score for that game session
	int score;
	// Player's highest recorded score
	int highScore;
	// Player object
	Player* player;
	// Obstacles
	std::vector <Obstacle*> obstacleList;
	// Holds status of player input
	std::string validInput;
	// Holds the list of valid commands
	std::vector <Verb*> verbVector;
	// Whether the game session is finished
	bool gameOver;
	// Whether to close the application
	bool quitGame;
	// Whether to restart the game
	bool restarting;

	// Print the game title at the top of the window
	void PrintGameName();
	// Print the player score
	void PrintScore();
	// Print the game area
	void PrintStage();
	// Print input status
	void PrintInputStatus();
	// Print the borders
	void PrintVerticalBorder();
	void PrintHorizontalBorder();
	// Print the player
	char PrintPlayer(int, int);
	// Print the obstacles
	char PrintObstacles(int, int);
	
	// Keep the player within the stage
	void ApplyStageBoundaries();

	// Generate the obstacles
	void GenerateObstacle();
	void RemoveObstacle(int);

	// Check collisions
	bool IntersectWithObstacle(Obstacle*, int, int);
	void CheckCollisions();

	// Read in the available commands
	void LoadVerbFile(std::string filePath);
	// Handle text input
	void VerbRoutine(int);

public:
	Game(void);
	~Game(void);

	// Getters
	bool GetQuitGame();
	bool GetRestart();

	// Draw the game window
	void Display();
	// Interpret user entered commands
	void ParseInput(std::string);
	// Game loop
	void Update(std::string);
};

#endif

