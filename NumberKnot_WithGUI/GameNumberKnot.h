#pragma once

#include "PuzzleManager.h"
#include "Puzzle.h"

/*Connects logic and graphical representation of application.*/
class GameNumberKnot
{
private:
	PuzzleManager manager;
	int width = 4; /*Width of the next puzzle created by GetNext() method.*/
	int height = 4; /*Height of the next puzzle created by GetNext() method.*/
	bool wasSecondTime = false; /*Tells if a puzzle with such dimensions was created for the second time.*/

	void ChangeParameters();

public:

	Puzzle * GetNext();

};

