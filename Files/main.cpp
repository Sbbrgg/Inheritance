#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_TO_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	//1) �������� ������:
	std::ofstream fout;
	//2) �������� ������:
	//fout.open("File.txt");	//����� ��������� ����� ������� ������ ����� �������������� ����.
	fout.open("File.txt", std::ios_base::app);
	//3) ������ � �����:
	fout << "Hello files" << endl;
	//4) ������ ����������� ����� ���������
	fout.close();

	system("notepad File.txt");
#endif // WRITE_TO_FILE

	//1) ������ � ��������� �����:
	std::ifstream fin("File.txt");

	//2) ��������� �������� �� �����: 
	if (fin.is_open())
	{
		//3) ������ �� �����:
		while (!fin.eof())	//EndOfFile
		{
			std::string buffer;
			//fin >> buffer;
			std::getline(fin, buffer);
			cout << buffer << endl;
		}
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}

	//?) ��������� �����:
	fin.close();
}