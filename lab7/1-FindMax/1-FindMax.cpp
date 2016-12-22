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
		{ "Артем", "Ребров", 193, 91},
		{ "Боккетти", "Сальвадоре", 186, 86},
		{ "Илья", "Кутепов", 192, 85 },
		{ "Евгений", "Макеев", 181, 73 },
		{ "Андрей", "Ещенко", 176, 74},
		{ "Дмитрий", "Комбаров", 182, 76},
		{ "Лукас", "Фернандо", 175, 80},
		{ "Денис", "Глушаков", 182, 82},
		{ "Квинси", "Промес", 174, 71},
		{ "Джано", "Ананидзе", 172, 64},
		{ "Зе", "Луиш", 184, 84 },
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

