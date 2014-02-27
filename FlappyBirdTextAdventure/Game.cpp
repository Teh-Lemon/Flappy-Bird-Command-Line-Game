#include "Game.h"
#include "Player.h"

// Constants
const int STAGE_WIDTH = 30;
const int STAGE_HEIGHT = 12;
const int PLAYER_X_POSITION = 3;
const int INTERVAL_OBSTACLES = 8;
const int START_PERIOD = 5;
const std::string DATA_FILE_PATH = "Data/data.dat";
const std::string VERBS_FILE_PATH = "Data/verbs.txt";
const std::string START_MSG = " Available: FLAP/F, RESTART/R, QUIT/Q or nothing at all \n Have fun - Teh Lemon";

// Game time
int timeCounter = 0;
// Used to format score/fps line
int scoreLength;
int fpsLength;

#pragma region Initialization
// Constructor
Game::Game(void)
{
	score = 0;
	highScore = 0;
	player = new Player();
	gameOver = false;
	quitGame = false;
	restarting = false;
	state = PLAYING;
	validInput = START_MSG;
	srand (time(NULL));

	scorePlusTune = new Tune("Data/Sounds/scorePlus.txt");
	gameOverTune = new Tune("Data/Sounds/gameOver.txt");

	LoadVerbFile(VERBS_FILE_PATH);
	ReadSavedData(DATA_FILE_PATH);
}

// Destructor
Game::~Game(void)
{
	delete player;
	delete scorePlusTune;
	delete gameOverTune;
	obstacleList.clear();
}

void Game::ReadSavedData(std::string filePath)
{	
	//	File to read in
	std::ifstream txtFile (filePath);
	//	Each line of text file
	std::string line;
	//	First field
	std::string field;
	//	Second field
	std::string value;

	//	Open the file and read in the saved data
	if (txtFile.is_open())
	{
		//	When file is ready to be read
		while (txtFile.good())
		{
			field = "";
			value = "";

			//	Read in a line
			std::getline (txtFile, line);

			//	Split the line by comma
			for (int i = 0; i < line.size(); ++i)
			{
				//	Second and third field
				if (line[i] == '=')
				{
					for (int j = i + 1; j < line.size(); ++j)
					{
						//	Second field
						value.push_back(line[j]);
					}	
					break;
				}
				//	First field
				else
				{
					field.push_back(line[i]);					
				}
			}

			LoadSavedData(field, value);
		}

		txtFile.close();
	}
}

void Game::LoadSavedData(std::string field, std::string value)
{
	// TODO: Rewrite this so it's not a giant if/else chain
	// RESEARCH: Map lookups with boost

	if (field == "highscore")
	{
		highScore = atoi(value.c_str());
	}
}

void Game::SaveSavedData(std::string filePath)
{
	//	File to read in
	std::ofstream txtFile (filePath);

	//Save the high score
	//	Open the file and read in the saved data
	if (txtFile.is_open())
	{
		txtFile.clear();
		txtFile << "highscore=" << highScore;

		txtFile.close();
	}
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
	std::cout << "      FLAPPY BIRD TEXT GAME" << std::endl;
	std::cout << " --------------------------------";
}

// Print the current score
void Game::PrintScore()
{
	// Print the score + update its length
	std::string scoreStr = "  Score: " + std::to_string(static_cast<long long>(score));
	scoreLength = scoreStr.size();

	std::cout << scoreStr;
}

void Game::PrintFPSCounter(double dt)
{
	if (dt > 0)
	{
		// Find the frame rate per hour
		double fps = 1 / dt;
		std::string fpsStr = "FPS: " + std::to_string(static_cast<long long>(fps));;
		fpsLength = fpsStr.size();

		// Right align to the stage
		for (int i = 0; i < fpsLength; i++)
		{
			std::cout << "\b";
		}

		std::cout << fpsStr;

	}
}


// Print the borders
void Game::PrintVerticalBorder()
{
	std::cout << " ";
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

char Game::PrintObstacles(int w, int h)
{
	// For each obstacle
	for (int i = 0; i < obstacleList.size(); i++)
	{
		if (IntersectWithObstacle(obstacleList[i], w, h))
		{
			return obstacleList[i]->GetShape();
		}
	}

	return NULL;
}

// Draw mountains at the bottom
char Game::PrintBackground(int x, int y)
{	
	// Draw peak of mountain
	if (y == STAGE_HEIGHT - 2)
	{
		if (x % 4 == 1)
		{
			return '/';
		}
		else if (x % 4 == 2)
		{
			return '\\';
		}
	}
	// Draw bottom of mountain
	if (y == STAGE_HEIGHT - 1)
	{
		if (x % 4 == 0)
		{
			return '/';
		}
		else if (x % 4 == 3)
		{
			return '\\';
		}
	}
	return NULL;
}

// Print the game area
void Game::PrintStage()
{
	// Draw the top border
	PrintVerticalBorder();

	// Draw the game row by row
	for (int h = 0; h < STAGE_HEIGHT; h++)
	{
		std::cout << " ";
		// Print the left borders
		PrintHorizontalBorder();

		// Draw cell by cell
		for (int w = 0; w < STAGE_WIDTH; w++)
		{
			char charToPrint = ' ';
			
			// Draw the background
			if (PrintBackground(w, h) != NULL)
			{
				charToPrint = PrintBackground(w, h);
			}

			// Draw the obstacles
			if (PrintObstacles(w, h) != NULL)
			{
				charToPrint = PrintObstacles(w, h);
			}

			// Draw the player
			if (PrintPlayer(w, h) != NULL)
			{
				charToPrint = PrintPlayer(w, h);
			}			

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
void Game::Display(float dt)
{
	std::cout << std::endl;

	// Print the game title
	PrintGameName();
	std::cout << std::endl;

	// Print the player score
	PrintScore();
	// Print a space between score and fps
	for (int i = 0; i < STAGE_WIDTH - scoreLength + 2; i++)
	{
		std::cout << " ";
	}
	// Print the fps counter
	PrintFPSCounter(dt);
	std::cout << std::endl;

	// Print the game stage
	PrintStage();

	// Print the previous input status
	PrintInputStatus();

	// Print the command line
	std::cout << " What will you do?: ";
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
	// Every time interval
	if (timeCounter % INTERVAL_OBSTACLES == 0)
	{
		// Create a new obstacle at the end of the screen
		obstacleList.push_back(new Obstacle(0, STAGE_WIDTH));

		// Randomize its height.
		// At least a height of 1
		// Below the top of the stage
		int height = (rand() % (STAGE_HEIGHT - obstacleList[0]->GetGapSize() - 1)) + 1;
		obstacleList.back()->SetHeight(height);
	}
}

void Game::RemoveObstacle(int i)
{
	delete obstacleList[i];
	obstacleList.erase(obstacleList.begin() + i);
}

bool Game::IntersectWithObstacle(Obstacle* obstacle, int x, int y)
{
		// Check x position are the same
		if (x == obstacle->GetPositionX())
		{
			// Check top half
			if (STAGE_HEIGHT - y > 
				obstacle->GetHeight() + obstacle->GetGapSize()) 
			{
				return true;
			}
			// Check bottom half
			else if (STAGE_HEIGHT - y <= obstacle->GetHeight())
			{
				return true;
			}
		}

		// Return false if no matches
		return false;
}

void Game::CheckCollisions()
{
	// For each obstacle
	for (int i = 0; i < obstacleList.size(); i++)
	{
		// Increase score when player passes an obstacle
		if (PLAYER_X_POSITION == obstacleList[i]->GetPositionX() + 1)
		{
			score++;
			queuedTunes.push_back(scorePlusTune);
		}

		// Remove obstacle when they go off the stage
		if (obstacleList[i]->GetPositionX() < 0)
		{
			RemoveObstacle(i);
		}

		// Check for intersection with obstacle by player
		// Set game over if true
		if (IntersectWithObstacle(obstacleList[i], PLAYER_X_POSITION, player->GetPositionY()))
		{
			ApplyGameOver();
		}

	}
}

void Game::ApplyGameOver()
{
	// Set the new high score if achieved
	if (score > highScore)
	{
		highScore = score;
		SaveSavedData(DATA_FILE_PATH);
	}

	// Change player shape
	player->SetPlayerShape('x');		
	// Play game over sound
	queuedTunes.push_back(gameOverTune);
	// Display game over message
	validInput = " GAME OVER. YOUR HIGH SCORE IS "
		+ std::to_string(static_cast<long long>(highScore)) + "\n" 
		+ " [RESTART, QUIT]";

	// Change the state
	state = GAME_OVER;
}
#pragma endregion

#pragma region sounds
// Play all the sounds that were queued up
void Game::PlaySounds()
{
	// Play each tune in the queue then empty it
	for (int i = 0; i < queuedTunes.size(); i++)
	{
		queuedTunes[i]->Play();
	}

	queuedTunes.clear();
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
	// Read in user text input
	ParseInput(input);

	switch (state)
	{
	case PLAYING:
		if (timeCounter > START_PERIOD)
		{
			// Generate a steady stream of obstacles
			GenerateObstacle();
		}

		// Update objects
		for (int i = 0; i < obstacleList.size(); i++)
		{
			obstacleList[i]->Update();
		}

		// Update player
		player->Update();

		// Keep the player within the stage
		ApplyStageBoundaries();

		// Check for collisions
		// Increase score for passing obstacles
		// Remove old obstacles
		// Check for collision between obstacle and player
		CheckCollisions();

		// Increase the clock
		timeCounter++;
		break;

	case GAME_OVER:
		validInput = " GAME OVER. YOUR HIGH SCORE IS "
			+ std::to_string(static_cast<long long>(highScore)) + "\n" 
			+ " [RESTART, QUIT]";
		break;

	default:
		break;
	}
}
#pragma endregion
