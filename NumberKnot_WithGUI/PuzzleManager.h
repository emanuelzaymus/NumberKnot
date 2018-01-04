#pragma once

#include <utility>

#include "Puzzle.h"

using namespace std;

/*XY directions of shift.*/
struct shift {
	int deltaX = 0;
	int deltaY = 0;

	bool operator< (const shift& struc) const { return (deltaX == struc.deltaX) ? (deltaY < struc.deltaY) : (deltaX < struc.deltaX); }
	bool operator== (const shift& struc) const { return deltaX == struc.deltaX && deltaY == struc.deltaY; }
};

/*Manager creates, reads, writes and returns Puzzle*.*/
class PuzzleManager
{
private:
	shift RotateDeltas(shift sh);
	shift RandDeltas(int x, int y, Table * tableOfProbability);	
	Table * CreateTableOfProbab(int width, int height);
	Table * RemoveNonexistingFields(Table * lines);
	Table * MakePuzzleForPlayer(Table * lines);

public:
	const char path_puzzles_puzzle[15] = "puzzles/puzzle";
	static const shift shiftDirect[8];

	PuzzleManager();

	Puzzle * CreatePuzzle(int width, int height, bool playable);
	Puzzle * GetNextPuzzle(int width, int height);
	Puzzle * ReadPuzzleFromFile(const string & path);
	void WritePuzzles(int width, int height, int count, int numberOfAttempts, int allowedZeros);

};
