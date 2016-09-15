#include <iostream>
#include <fstream>
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
		cout << "Can't open file " << argv[1];
		return 2;
	}
	//открыть файл для записи
	ofstream outFile(argv[2]);
	//пока входной файл не закончился
		// считываем записываем
	//
	return 0;
}