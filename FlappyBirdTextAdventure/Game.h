#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

#include "Player.h"
#include "Verb.h"
#include "Obstacle.h"
#include "Note.h"
#include "Tune.h"

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
	// States
	enum { PLAYING, GAME_OVER };
	int state;

	// Draw methods
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
	// Draw the background
	char PrintBackground(int, int);

	// Generate the obstacles
	void GenerateObstacle();
	void RemoveObstacle(int);

	// Collision methods
	// Check collisions
	bool IntersectWithObstacle(Obstacle*, int, int);
	void CheckCollisions();
	// Keep the player within the stage
	void ApplyStageBoundaries();
	// Set game over
	void ApplyGameOver();

	// Sound
	// Sound for when the score increases
	Tune* scorePlusTune;
	// Sound for when it is game over
	Tune* gameOverTune;
	// List of tunes queued up to be played next frame
	std::vector <Tune*> queuedTunes;

	// Read in the available commands
	void LoadVerbFile(std::string filePath);
	// Handle text input
	void VerbRoutine(int);
	// Load the high score from file
	void ReadSavedData(std::string);
	void LoadSavedData(std::string, std::string);
	// Save new high score
	void SaveSavedData(std::string);

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
	// Play sounds	
	void PlaySounds();
};

#endif

