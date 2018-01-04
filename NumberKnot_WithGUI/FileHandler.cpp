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
	//if (!(experimental::filesystem::exists(path)));
	//{
	//	printf("...neotvorene\n");
	//	if (experimental::filesystem::create_directory(path))
	//		printf("....vytvorene\n");
	//}

	ofstream outFile(path);
	if (outFile.is_open())
	{
		outFile << text;
		outFile.close();
	}
	else
		printf("!!! File %s was not opened !!!\n", path);
}

/*Returns whole content of file (file path = path param).*/
string FileHandler::Read(const string & path)
{
	ifstream inFile(path);
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

	if (inFile.is_open()) {
		while (!inFile.eof()) {
			getline(inFile, line);
			count++;
		}
		inFile.close();
	}
	return count;
}
