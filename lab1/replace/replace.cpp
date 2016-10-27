#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string replace(string str, const string strFind, const string strReplace)
{
	string resultStr;
	size_t findLength = strFind.length();
	size_t lastPlace = 0;
	size_t findPlace = str.find(strFind, lastPlace);
	while (findPlace != string::npos)
	{
		resultStr.append(str, lastPlace, findPlace - lastPlace);
		resultStr.append(strReplace);
		lastPlace = findPlace + findLength;
		findPlace = str.find(strFind, lastPlace);
	}
	resultStr.append(str, lastPlace, string::npos);
	return resultStr;
}

int main(int argv, char *argc[])
{
	if (argv != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}
	if (!strlen(argc[4]))
	{
		cerr << "search stirng can't be empty\n";
		return 1;
	}
	//открыть файл для чтения
	ifstream inFile(argc[1]);
	if (!inFile.is_open())
	{
		cerr << "Can't open input file " << argc[1] << endl;
		return 2;
	}
	ofstream outFile(argc[2]);
	if (!outFile.is_open())
	{
		cerr << "Can't open output file " << argc[2] << endl;
		return 2;
	}

	string str;
	while (getline(inFile, str))
	{
		outFile << replace(str, argc[3], argc[4]) << endl;
		// replace
	}

	if (!outFile.flush())
	{
		cerr << "Failed to save data on disk";
		return 2;
	}
	
	return 0;
}