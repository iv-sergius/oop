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
	//������� ���� ��� ������
	ifstream inFile(argv[1]);
	if (!inFile.is_open())
	{
		cout << "Can't open file " << argv[1];
		return 2;
	}
	//������� ���� ��� ������
	ofstream outFile(argv[2]);
	//���� ������� ���� �� ����������
		// ��������� ����������
	//
	return 0;
}