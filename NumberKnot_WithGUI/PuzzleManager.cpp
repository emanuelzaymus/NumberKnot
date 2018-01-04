#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

#include "PuzzleManager.h"
#include "Puzzle.h"
#include "FileHandler.h"
#include "Table.h"

using namespace std;

shift shUp = { 0,-1 };
shift shRight = { 1,0 };
shift shDown = { 0,1 };
shift shLeft = { -1,0 };

shift shUpRight = { 1,-1 };
shift shDownRight = { 1,1 };
shift shDownLeft = { -1,1 };
shift shUpLeft = { -1,-1 };

const shift PuzzleManager::shiftDirect[8] = { shUp, shUpRight, shRight, shDownRight, shDown, shDownLeft, shLeft, shUpLeft };

/*Returns shift rotated clockwise.*/
shift PuzzleManager::RotateDeltas(shift sh)
{
	int deltaX = sh.deltaX;
	int deltaY = sh.deltaY;
	if (deltaX == 1 && deltaY != 1)
		deltaY++;
	else if (deltaY == 1 && deltaX != -1)
		deltaX--;
	else if (deltaX == -1 && deltaY != -1)
		deltaY--;
	else if (deltaY == -1 && deltaX != 1)
		deltaX++;
	return shift() = { deltaX, deltaY };
}

/*Returns shift from XY positon based on tableOfProbability.*/
shift PuzzleManager::RandDeltas(int x, int y, Table * tableOfProbability)
{
	double randNum = (double)rand() / (RAND_MAX);
	int sum = 0;
	int newX, newY;
	map<shift, double> choices;

	for (shift s : shiftDirect)
	{
		newX = x + s.deltaX;
		newY = y + s.deltaY;
		if (tableOfProbability->AreInBounds(newX, newY))
		{
			sum += tableOfProbability->Get(newY, newX);
			choices[s] = tableOfProbability->Get(newY, newX);
		}
	}
	double sumOfProbab = 0;
	for (map<shift, double>::iterator it = choices.begin(); it != choices.end(); it++) {
		sumOfProbab += it->second / sum;
		if (randNum < sumOfProbab)
			return it->first;
	}
	return shift() = { 0,0 };
}

/*Returns tableofProbability with width-height dimensions.*/
Table * PuzzleManager::CreateTableOfProbab(int width, int height)
{
	Table * tableOfProbability = new Table(width, height);
	int probab;
	for (size_t i = 0; i < height / 2 + 1; i++)
		for (size_t j = 0; j < width / 2 + 1; j++)
		{
			probab = pow(i * j + 1, 1);
			tableOfProbability->Put(i, j, probab);
			tableOfProbability->Put(i, width - j - 1, probab);
			tableOfProbability->Put(height - i - 1, j, probab);
			tableOfProbability->Put(height - i - 1, width - j - 1, probab);
		}
	return tableOfProbability;
}

/*Replaces all 0 with -1.*/
Table * PuzzleManager::RemoveNonexistingFields(Table * lines)
{
	for (size_t i = 0; i < lines->GetHeight(); i++)
		for (size_t j = 0; j < lines->GetWidth(); j++)
			if (lines->Get(i, j) == 0)
				lines->Put(i, j, -1);

	return lines;
}

/*Creates playable puzzle lines with cleared fields.*/
Table * PuzzleManager::MakePuzzleForPlayer(Table * lines)
{
	Table * ret = new Table(lines->GetWidth(), lines->GetHeight());

	for (size_t i = 0; i < lines->GetHeight(); i++)
		for (size_t j = 0; j < lines->GetWidth(); j++)
			if (lines->Get(i, j) < 0)
				ret->Put(i, j, -1);

	int x;
	for (size_t y = 0; y < lines->GetHeight(); y++)
	{
		for (size_t i = 0; i < 2; i++)
		{
			x = rand() % lines->GetWidth();
			if (lines->Get(y, x) > 0)
				ret->Put(y, x, lines->Get(y, x));
		}
	}
	delete lines;
	return ret;
}

/*Randomizes according to the time.*/
PuzzleManager::PuzzleManager()
{
	srand(time(NULL));
}

/*Creates playable/"nonplayable" puzzle with width-height dimensions.*/
Puzzle * PuzzleManager::CreatePuzzle(int width, int height, bool playable = true)
{
	if (width == 0 || height == 0)
		return nullptr;

	Table * tableOfProbability = CreateTableOfProbab(width, height);
	Table * lines = new Table(width, height);

	int x(rand() % width), y(rand() % height);
	int i = 1;
	bool noEnd(true), changeDeltas(false);
	shift deltas, earlierDeltas = { 0,0 };

	do {
		if (lines->AreInBounds(x + deltas.deltaX, y + deltas.deltaY))
		{
			if (lines->Get(y + deltas.deltaY, x + deltas.deltaX) == 0)
			{
				lines->Put(y + deltas.deltaY, x + deltas.deltaX, i);
				i++;
				x += deltas.deltaX;
				y += deltas.deltaY;
				do {
					deltas = RandDeltas(x, y, tableOfProbability);
				} while (deltas == (shift() = { 0,0 }));
				earlierDeltas = deltas;
			}
			else { changeDeltas = true; }
		}
		else { changeDeltas = true; }

		if (changeDeltas) {
			changeDeltas = false;
			deltas = RotateDeltas(deltas);

			if (earlierDeltas == deltas)
				noEnd = false;
		}
	} while (noEnd);

	delete tableOfProbability;

	lines = RemoveNonexistingFields(lines);
	if (playable)
		lines = MakePuzzleForPlayer(lines);

	lines->UpdateOriginalLines();
	return new Puzzle(*lines);
}

/*Returns playable puzzle loaded from file (file paht = path param).*/
Puzzle * PuzzleManager::ReadPuzzleFromFile(const string & path)
{
	FileHandler fh;
	string input = fh.Read(path);
	int height = fh.NumberOfLines(path);

	istringstream iss(input);
	vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>{});
	int width = tokens.size() / height;

	Table * lines = new Table(width, height);
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			lines->Put(i, j, stoi(tokens[i * width + j]));

	lines = RemoveNonexistingFields(lines);
	lines = MakePuzzleForPlayer(lines);
	lines->UpdateOriginalLines();
	return new Puzzle(*lines);
}

/*Returns random puzzle with width-height dimensions loaded from file.*/
Puzzle * PuzzleManager::GetNextPuzzle(int width, int height)
{
	char path[25];
	int number = (rand() % 10) + 1;
	snprintf(path, sizeof(path), "%s%dx%d_%d.txt", path_puzzles_puzzle, width, height, number);
	return ReadPuzzleFromFile(path);
}

/*Writes width-height dimensional puzzle; count of puzzles; numberOfAttempts 
on which it will try to creat such puzzles (more than 1000 recommended), count of allowedZeros in puzzles.*/
void PuzzleManager::WritePuzzles(int width, int height, int count, int numberOfAttempts = 1000, int allowedZeros = 0)
{
	FileHandler fh;
	char path[25];
	int numberOfCreated = 0;

	for (size_t i = 0; i < numberOfAttempts; i++)
	{
		Puzzle * p = CreatePuzzle(width, height, false);
		if (p->GetCountOfNonexistingFields() <= allowedZeros)
		{
			numberOfCreated++;
			snprintf(path, sizeof(path), "%s%dx%d_%d.txt", path_puzzles_puzzle, width, height, numberOfCreated);
			cout << path << "    was written. Attempt number: " << i << endl;
			fh.Write(path, p->ToString());
			if (numberOfCreated == count)
				return;
		}
		delete p;
	}
}
