#pragma once

using namespace std;

/*Class for writting and reading from files.*/
class FileHandler
{
public:
	void  Write(const string & path, const string & text);
	string Read(const string & path);
	int NumberOfLines(const string & path);
};
