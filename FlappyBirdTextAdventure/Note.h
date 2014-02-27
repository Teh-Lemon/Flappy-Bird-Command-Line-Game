#ifndef NOTE_H
#define NOTE_H

#include <windows.h>

class Note
{
private:
	// Frequency in Hz
	float frequency;
	// Duration in ms
	int duration;

public:
	Note(float, int);
	~Note(void);

	// Play note
	void Play();

	void SetFrequency(float);
	void SetDuration(int);
};


#endif
