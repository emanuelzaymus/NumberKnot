#pragma once

#include "Table.h"

/*Puzzle for player; offers basic communication; main logic.*/
class Puzzle : public Table
{
private:
	int nextNumToPut = 1; /*Number which will be put into table in the next PutNumber call.*/
	const int countOfFields = GetCountOfFields(); /*Count of existing fields in table (fields which are greater or equal 0).*/

	void SetNextNumToPut();

public:
	Puzzle(int width, int height, int **lines);
	Puzzle(Table & table);
	Puzzle(const Puzzle& obj) = delete;

	bool PutNumber(int y, int x);
	void StepBack();
	void Reset();
	bool CheckSolution();
	int GetNextNumber() { return nextNumToPut; }

};

