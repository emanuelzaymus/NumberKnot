#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>

#include "Table.h"

using namespace std;

/*Returns empty/copied width-height dimensional table.*/
int ** Table::MakeLines(int width, int height, int ** lines = nullptr)
{
	int ** ret = new int*[height];
	for (size_t i = 0; i < height; i++)
	{
		ret[i] = new int[width] {0};
		if (lines != nullptr)
		{
			for (size_t j = 0; j < width; j++)
				ret[i][j] = lines[i][j];
		}
	}
	return ret;
}

/*Deletes lines.*/
void Table::DelLines(int ** lines)
{
	for (size_t i = 0; i < height; i++)
		delete[] lines[i];
	delete[] lines;
}

/*Checks if table contains searched int.*/
bool Table::Contains(int searched)
{
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			if (lines[i][j] == searched)
				return true;
	return false;
}

/*Returns value greater than num and is the greatest in the row so far.*/
int Table::GetGreaterThanInRow(int num)
{
	while (Contains(num))
		num++;
	return num;
}

/*Returns count of existing fields in table (fields which are greater or equal 0).*/
unsigned int Table::GetCountOfFields()
{
	return width * height - GetCountOfNonexistingFields();
}

/*Replaces originalVal with newValue; returns bool if it was successful.*/
bool Table::ReplaceValue(int originalVal, int newValue)
{
	pair<int, int> p = GetPosition(originalVal);
	if (p.first >= 0 && p.second >= 0)
		if (originalLines[p.first][p.second] == 0)
		{
			lines[p.first][p.second] = newValue;
			return true;
		}
	return false;
}

/*Returns position of the first found element in table which equals value param; member first returns y-position, second reutrns x-position.*/
pair<int, int> Table::GetPosition(int value)
{
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			if (lines[i][j] == value)
				return pair<int, int>(i, j);
	return pair<int, int>(-1, -1);
}

/*Resets table to original state.*/
void Table::Reset()
{
	DelLines(lines);
	lines = MakeLines(width, height, originalLines);
}

/*Creates width-height dimensional table filled with 0s.*/
Table::Table(int width, int height) : width(width), height(height)
{
	lines = MakeLines(width, height);
	originalLines = MakeLines(width, height);
}

/*Creates width-height dimensional table filled with lines.*/
Table::Table(int width, int height, int ** lines) : width(width), height(height), lines(lines)
{
	originalLines = MakeLines(width, height, lines);
}

/*Deletes whole table.*/
Table::~Table()
{
	DelLines(lines);
	DelLines(originalLines);
}

ostream & operator<<(ostream & os, const Table & obj)
{
	char buff[10];
	for (size_t i = 0; i < obj.height; i++)
	{
		for (size_t j = 0; j < obj.width; j++)
		{
			if (obj.lines[i][j] <= -1)
				snprintf(buff, sizeof(buff), "%3d", -1);
			else
				snprintf(buff, sizeof(buff), "%3d", obj.lines[i][j]);

			os << buff;
		}
		if (i < obj.height - 1)
			os << "\n";
	}
	return os;
}

/*Updates originalLines in table which are initial state of table.*/
void Table::UpdateOriginalLines()
{
	DelLines(originalLines);
	originalLines = MakeLines(width, height, lines);
}

/*Returns count of nonexisting fields in table (fields which are less than 0);*/
unsigned int Table::GetCountOfNonexistingFields()
{
	unsigned int count = 0;
	for (size_t k = 0; k < height; k++)
		for (size_t m = 0; m < width; m++)
			if (lines[k][m] < 0) {
				count++;
			}
	return count;
}

/*Returns string with text-based representation of table.*/
string Table::ToString()
{
	ostringstream oss;
	oss << *this;
	return oss.str();
}

/*Prints text-based representation of table.*/
void Table::Print()
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			if (lines[i][j] <= -1)
				printf("%3s", "");
			else
				printf("%3d", lines[i][j]);
		}
		printf("\n");
	}
}
