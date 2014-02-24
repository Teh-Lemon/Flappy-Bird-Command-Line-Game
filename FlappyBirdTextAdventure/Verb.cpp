//	Holds the verb keyword

#include "Verb.h";

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

//	Constructor
Verb::Verb (int numberValue, string wordValue, bool isSingleValue) 
	:	number(numberValue), verb(wordValue), isSingleWord(isSingleValue)
{
	//cout << "VERB INITIALIZED: " << number << " " << verb << " " << isSingleValue << endl;
	//std::cin >> wordValue;
}

//	Destructor
Verb::~Verb()
{
}

//	Keyword getters/setters
string Verb::getVerb()
{
	return verb;
}

int Verb::getNumber()
{
	return number;
}

bool Verb::getIsSingleWord()
{
	return isSingleWord;
}