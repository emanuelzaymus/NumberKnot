#pragma once
#include <string>

using namespace std;

/*Basic rectangular table of integers; simple operations.*/
class Table
{
private:
	int width;
	int height;
	int ** lines;
	int ** originalLines; /*Lines which are initial state of table*/

	int ** MakeLines(int width, int height, int ** lines);
	void DelLines(int ** lines);
	bool Contains(int searched);

protected:
	int GetGreaterThanInRow(int num);
	bool ReplaceValue(int original, int newValue);
	pair<int, int> GetPosition(int value);
	void Reset();

public:
	Table(int width, int height);
	Table(int width, int height, int ** lines);
	~Table();

	friend ostream& operator<< (ostream& os, const Table& obj);

	int GetWidth() { return width; };
	int GetHeight() { return height; };
	bool AreInBounds(int x, int y) { return ((0 <= x) && (x < width) && (0 <= y) && (y < height)); };

	void UpdateOriginalLines();

	void Put(int y, int x, int value) { lines[y][x] = value; };
	int Get(int y, int x) { return lines[y][x]; };

	unsigned int GetCountOfFields();
	unsigned int GetCountOfNonexistingFields();
	string ToString();
	void Print();
};
