#include "Note.h"


Note::Note(float freq, int dura)
	: frequency(freq), duration(dura)
{
}


Note::~Note(void)
{
}

void Note::Play()
{
	// A note
	if (frequency > 0) 
	{
		Beep(frequency, duration);
	} 
	// A rest
	else 
	{
		Sleep(duration);
	}
}

void Note::SetFrequency(float freq)
{
	frequency = freq;
}

void Note::SetDuration(int dura)
{
	duration = dura;
}
