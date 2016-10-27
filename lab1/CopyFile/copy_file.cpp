#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) 
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: CopyFile.exe <input file> <output file> \n";
		return 1;
	}
	//открыть файл для чтения
	ifstream inFile(argv[1]);
	if (!inFile.is_open())
	{
		cout << "Can't open input file " << argv[1] << endl;
		return 2;
	}
	//открыть файл для записи
	ofstream outFile(argv[2]);
	if (!outFile.is_open())
	{
		cout << "Can't open output file " << argv[2] << endl;
		return 2;
	}
	
	//пока входной файл не закончился
		// считываем записываем
	char ch;
	while (inFile.get(ch))
	{
		if (!outFile.put(ch))
		{
			cout << "Failed to save data on disk";
			return 2;
		}
	}

	if (!outFile.flush())
	{
		cout << "Failed to save data on disk";
		return 2;
	}
	return 0;
}