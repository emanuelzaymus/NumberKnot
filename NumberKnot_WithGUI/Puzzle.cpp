#include "Puzzle.h"
#include "PuzzleManager.h"

/*Sets nextNumToPut by a value which is greater than the greatest value in row so far.*/
void Puzzle::SetNextNumToPut()
{
	nextNumToPut = GetGreaterThanInRow(nextNumToPut);
}

/*Creates puzzle based on lines param.*/
Puzzle::Puzzle(int width, int height, int **lines) : Table(width, height, lines)
{
	SetNextNumToPut();
}

/*Creates puzzle based on table param; table is used for implicit Table copy-constructor.*/
Puzzle::Puzzle(Table & table) : Table(table)
{
	SetNextNumToPut();
}

/*Puts next number into YX position.*/
bool Puzzle::PutNumber(int y, int x)
{
	if (Get(y, x) != 0)
		return false;

	Put(y, x, nextNumToPut);
	nextNumToPut++;
	SetNextNumToPut();
	if (nextNumToPut > countOfFields)
		return CheckSolution();

	return false;
}

/*One step back.*/
void Puzzle::StepBack()
{
	if (nextNumToPut == 1)
		return;

	while (!ReplaceValue(nextNumToPut - 1, 0))
	{
		nextNumToPut--;
	}
	nextNumToPut--;
	SetNextNumToPut();
}

/*Resets whole puzzle.*/
void Puzzle::Reset()
{
	Table::Reset();
	nextNumToPut = 1;
	SetNextNumToPut();
}

/*Checks if the solution is solved correctly.*/
bool Puzzle::CheckSolution()
{
	int value = 1, lastValue = 1;
	pair<int, int> p = GetPosition(value);
	int x = p.second, y = p.first;
	int newX, newY;

	do
	{
		lastValue = value;
		for (shift s : PuzzleManager::shiftDirect)
		{
			newX = x + s.deltaX;
			newY = y + s.deltaY;
			if (AreInBounds(newX, newY))
				if (Get(newY, newX) == value + 1) {
					x = newX;
					y = newY;
					if (++value == countOfFields)
						return true;
					break;
				}
		}
	} while (value != lastValue);
	return false;
}
