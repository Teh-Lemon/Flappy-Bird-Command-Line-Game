// Flappy Bird Text Adventure game
// Created on 23/02/2014 by Teh Lemon

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Game.h";

void InitializeGame();
Game* game;
// States

int main()
{
	// While the game is still running
	bool gameRunning = true;
	std::string userInput = "";

	// Initialize the game
	InitializeGame();

	// Game update loop
	do
	{
		// Clear the console window
		system("cls");

		// Display the game stage
		game->Display();

		// Play any sounds		
		game->PlaySounds();

		// Take in user input
		std::getline(std::cin, userInput);
		game->Update(userInput);
		std::cout << std::endl;

		//	Listen for quit or restart commands
		if (game->GetQuitGame())
		{
			gameRunning = false;
		}
		else if (game->GetRestart())
		{
			InitializeGame();
		}

	} while (gameRunning);

	// De-allocate memory
	delete game;

	return 0;
}

void InitializeGame()
{
	if (game != NULL)
	{
		delete game;
	}

	game = new Game();
	return;
}