#include <fstream>
#include <cstdio>
#include <filesystem> //getline
//#include <string>
//#include <sstream>

#include "FileHandler.h"

using namespace std;

/*Writes string in text param into file (file path = path param).*/
void FileHandler::Write(const string & path, const string & text)
{
	ofstream outFile(path);
	outFile << text;
	outFile.close();
}

/*Returns whole content of file (file path = path param).*/
string FileHandler::Read(const string & path)
{
	ifstream inFile(path);
	if (!inFile.is_open())
	{
		System::Windows::Forms::MessageBox::Show("Cannot read file.", "Problem");
	}
	string ret((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	inFile.close();

	//stringstream strStream;		//ver 2
	//strStream << inFile.rdbuf();
	//ret = strStream.str();

	//getline(inFile, ret, (char)inFile.eof());		//ver 3

	return ret;
}

/*Returns number of lines in file (file path = path param).*/
int FileHandler::NumberOfLines(const string & path)
{
	ifstream inFile(path);
	int count = 0;
	string line;

	if (!inFile.is_open())
		System::Windows::Forms::MessageBox::Show("Cannot read file.", "Problem");

	while (!inFile.eof()) {
		getline(inFile, line);
		count++;
	}
	inFile.close();

	return count;
}
