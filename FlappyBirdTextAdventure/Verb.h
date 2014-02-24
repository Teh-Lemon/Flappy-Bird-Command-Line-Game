//	Holds the verb keyword

#ifndef VERB_H
#define VERB_H

#include <iostream>
#include <string>

class Verb
{

private:
	//	ID
	int number;
	//	Verb keyword
	std::string verb;
	//	Is it a single word command
	bool isSingleWord;

public:
	//	number, verb
	Verb(int, std::string, bool);
	~Verb();

	//	getter
	std::string getVerb();
	int getNumber();
	bool getIsSingleWord();
	
};

#endif