#include "Game.h"
#include "Player.h"

// Constants
const int STAGE_HEIGHT = 12;
const int STAGE_WIDTH = 30;
const int PLAYER_X_POSITION = 3;

#pragma region Initialization
// Constructor
Game::Game(void)
{
	score = 0;
	highScore = 0;
	player = new Player();
	validInput = "";
	gameOver = false;
	quitGame = false;
	restarting = false;

	GenerateObstacle();

	LoadVerbFile("verbs.txt");
}

// Destructor
Game::~Game(void)
{
	delete player;
}

//	Load in the valid commands from the text files
void Game::LoadVerbFile(std::string filePath)
{
	//	File to read in
	std::ifstream txtFile (filePath);
	//	Each line of text file
	std::string line;
	//	First field
	std::string number;
	//	Second field
	std::string verb;
	//	Third field
	std::string single;
	bool isSingle;

	//	Open the file
	if (txtFile.is_open())
	{
		//	When file is ready to be read
		while (txtFile.good())
		{
			number = "";
			verb = "";
			single = "";

			//	Read in a line
			std::getline (txtFile, line);

			//	Split the line by comma
			for (int i = 0; i < line.size(); ++i)
			{
				//	Second and third field
				if (line[i] == ',')
				{
					for (int j = i + 1; j < line.size(); ++j)
					{
						//	Third field
						if (line[j] == ',')
						{
							for (int k = j + 1; k < line.size(); ++k)
							{
								single.push_back(line[k]);
							}	
							break;
						}
						//	Second field
						else
						{
							verb.push_back(line[j]);
						}
					}	
					break;
				}
				//	First field
				else
				{
					number.push_back(line[i]);					
				}
			}

			//	Convert true or false into boolean values
			if (single == "true")
			{
				isSingle = true;
			}
			else
			{
				isSingle = false;
			}

			//	Initialize and add object to list
			verbVector.push_back(new Verb(atoi(number.c_str()), verb, isSingle));
		}

		txtFile.close();
	}
}
#pragma endregion

#pragma region Getters/Setters
// Getter for quitGame
bool Game::GetQuitGame()
{
	return quitGame;
}

// Getter for restarting
bool Game::GetRestart()
{
	return restarting;
}
#pragma endregion

#pragma region Drawing
// Print the game title
void Game::PrintGameName()
{
	std::cout << "FLAPPY BIRD TEXT ADVENTURE" << std::endl;
}

// Print the current score
void Game::PrintScore()
{
	std::cout << "Score: " << score << std::endl;
}

// Print the borders
void Game::PrintVerticalBorder()
{
	for (int i = 0; i < STAGE_WIDTH + 2; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;
}
void Game::PrintHorizontalBorder()
{
	std::cout << "*";
}

// Print the player
char Game::PrintPlayer(int w, int h)
{
	if (w == PLAYER_X_POSITION && h == player->GetPositionY())
	{
		return player->GetPlayerShape();
	}
	else
	{
		return NULL;
	}
}

// Print the game area
void Game::PrintStage()
{
	// Draw the top border
	PrintVerticalBorder();

	// Draw the game row by row
	for (int h = 0; h < STAGE_HEIGHT; h++)
	{
		// Print the left borders
		PrintHorizontalBorder();

		// Draw cell by cell
		for (int w = 0; w < STAGE_WIDTH; w++)
		{
			char charToPrint = ' ';

			// Draw the player
			if (PrintPlayer(w, h) != NULL)
			{
				charToPrint = PrintPlayer(w, h);
			}

			// Draw the obstacles

			std::cout << charToPrint;
		}

		// Print the right border
		PrintHorizontalBorder();
		std::cout << std::endl;
	}

	// Draw the bottom border
	PrintVerticalBorder();
}

// Print the status of the entered command
void Game::PrintInputStatus()
{
	std::cout << validInput << std::endl;
}

// Draw the window
void Game::Display()
{
	std::cout << std::endl;

	// Print the game title
	PrintGameName();
	std::cout << "---------------------------" << std::endl;
	std::cout << std::endl;

	// Print the player score
	PrintScore();
	//std::cout << std::endl;

	// Print the game stage
	PrintStage();

	// Print the previous input status
	PrintInputStatus();

	// Print the command line
	std::cout << "Command: ";
}
#pragma endregion

#pragma region Game Logic
// Handle text input
void Game::VerbRoutine(int ID)
{	
	// Flapping
	if (ID == 0)
	{
		player->Flap();
	}

	// Restarting the game session
	if (ID == 1)
	{
		restarting = true;
	}

	// Quitting the game
	if (ID == 2)
	{
		quitGame = true;
	}
}

// Collision detection for floor and ceiling
void Game::ApplyStageBoundaries()
{
	// Stop player falling through floor
	if (player->GetPositionY() > STAGE_HEIGHT - 1)
	{
		player->SetPositionY(STAGE_HEIGHT - 1);
		player->SetVelocityY(0);
	}
	// Stop player flying through ceiling
	else if (player->GetPositionY() < 0)
	{
		player->SetPositionY(0);
		player->SetVelocityY(0);
	}
}

void Game::GenerateObstacle()
{
	obstacleList.push_back(new Obstacle());
}
#pragma endregion

#pragma region Update loop
void Game::ParseInput(std::string input)
{
	// The commands
	std::string verb = "";
	// ID of commands
	int vbID = -1;

	// Convert the word to upper case
	for (int i = 0; i < input.size(); i++)
	{
		input[i] = toupper(input[i]);
	}

	// Split the text input
	std::stringstream ss(input);	
	ss >> verb;

	// Find the verb in the verb list
	for (int i = 0; i < verbVector.size(); ++i)
	{
		if (verbVector[i]->getVerb() == verb)
		{
			vbID = verbVector[i]->getNumber();
			break;
		}
	}

	//	Check if valid
	if (vbID >= 0)
	{
		validInput = "";
		VerbRoutine(vbID);
	}
	else
	{
		if (input.size() > 0)
		{
			validInput = "INVALID COMMAND";
		}
		else
		{
			validInput = "";
		}
	}
}

void Game::Update(std::string input)
{
	ParseInput(input);

	player->Update();

	ApplyStageBoundaries();
}
#pragma endregion
