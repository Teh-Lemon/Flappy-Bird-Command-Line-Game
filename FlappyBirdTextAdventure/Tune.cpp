#include "Tune.h"


Tune::Tune(std::string filePath = "")
{
	if (filePath.size() > 0)
	{
		LoadFromFile(filePath);
	}
}


Tune::~Tune(void)
{
	notes.clear();
}

void Tune::LoadFromFile(std::string filePath)
{
	//	File to read in
	std::ifstream txtFile (filePath);
	//	Each line of text file
	std::string line;
	//	First field
	std::string freq;
	//	Second field
	std::string dura;

	//	Open the file and read in the saved data
	if (txtFile.is_open())
	{
		//	When file is ready to be read
		while (txtFile.good())
		{
			freq = "";
			dura = "";

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
						//	Second field
						dura.push_back(line[j]);
					}	
					break;
				}
				//	First field
				else
				{
					freq.push_back(line[i]);					
				}
			}

		AddNote(new Note(atof(freq.c_str()), atoi(dura.c_str())));
		}

		txtFile.close();
	}
}

// Add a note to the tune
void Tune::AddNote(Note* newNote)
{
	notes.push_back(newNote);
}

// Play the tune
void Tune::Play()
{
	for (int i = 0; i < notes.size(); i++)
	{
		notes[i]->Play();
	}
}
