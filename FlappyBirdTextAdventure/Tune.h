#ifndef TUNE_H
#define TUNE_H

#include <string>
#include <fstream>
#include <vector>
#include "Note.h"

class Tune
{
private:
	std::vector<Note*> notes;
public:
	Tune(std::string);
	~Tune(void);

	// Load the tune from a file
	void LoadFromFile(std::string filePath);
	// Add a note to the end of the tune
	void AddNote(Note*);
	// Play the tune
	void Play();
};

#endif
