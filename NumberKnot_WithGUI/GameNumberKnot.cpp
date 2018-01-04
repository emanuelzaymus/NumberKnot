#include "GameNumberKnot.h"
#include "PuzzleManager.h"
#include "Puzzle.h"

/*Increases attributes widht, height if wasSecondTime is true*/
void GameNumberKnot::ChangeParameters()
{
	if (wasSecondTime)
	{
		if (width == 4 && height == 4)
			width++;
		else if (width == 5 && height == 4)
			height++;
		else if (width == 5 && height == 5)
			height++;
		else if (width == 5 && height == 6)
			width++;
		else if (width == 6 && height == 6)
			width++;
		else if (width == 7 && height == 6)
			height++;
	}
	wasSecondTime = !wasSecondTime;
}

/*Returns new puzzle loaded from PuzzleManager manager; Calls ChangeParameters().*/
Puzzle * GameNumberKnot::GetNext()
{
	Puzzle * p = manager.GetNextPuzzle(width, height);
	ChangeParameters();
	return p;
}
