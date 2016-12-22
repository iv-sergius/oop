// 1-FindMax.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "1-FindMax.h"
#include <cmath>

struct SSportsman
{
	std::string name;
	std::string surname;
//	std::string patronymic;
	int height;
	int weight;
};

int main()
{
	std::vector<SSportsman> team = {
		{ "�����", "������", 193, 91},
		{ "��������", "����������", 186, 86},
		{ "����", "�������", 192, 85 },
		{ "�������", "������", 181, 73 },
		{ "������", "������", 176, 74},
		{ "�������", "��������", 182, 76},
		{ "�����", "��������", 175, 80},
		{ "�����", "��������", 182, 82},
		{ "������", "������", 174, 71},
		{ "�����", "��������", 172, 64},
		{ "��", "����", 184, 84 },
	};

	auto LessHeight = [](const auto &lhs, const auto & rhs) {
		return lhs.height < rhs.height ? true : false;
	};

	setlocale(0, "");
	SSportsman footballer;
	FindMaxEx(team, footballer, LessHeight);
	std::cout << footballer.name << ' ' << footballer.surname << std::endl;

    return 0;
}

