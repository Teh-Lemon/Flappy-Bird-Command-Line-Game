#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>
#include <conio.h>
#include <iostream>

//default text colors can be found in wincon.h
inline void SetTextColor(WORD colors, bool colorsOn)
{
	if (colorsOn)
	{
		HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
  
		SetConsoleTextAttribute(hConsole, colors);
	}
}

#endif