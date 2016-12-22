// 1-FindMax-tests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../1-FindMax.h"

struct SSportsman
{
	std::string name;
	std::string surname;
	//	std::string patronymic;
	int height;
	int weight;
};

void CheckSportsmansEquality(SSportsman const & sportsman1, SSportsman const & sportsman2)
{
	BOOST_CHECK_EQUAL(sportsman1.name, sportsman2.name);
	BOOST_CHECK_EQUAL(sportsman1.surname, sportsman2.surname);
	BOOST_CHECK_EQUAL(sportsman1.height, sportsman2.height);
	BOOST_CHECK_EQUAL(sportsman1.weight, sportsman2.weight);
}

SSportsman keeper = { "Артем", "Ребров", 193, 91 };

std::vector<SSportsman> emptyVector;
std::vector<SSportsman> team = {
	keeper,
	{ "Боккетти", "Сальвадоре", 186, 86 },
	{ "Илья", "Кутепов", 192, 85 },
	{ "Евгений", "Макеев", 181, 73 },
	{ "Андрей", "Ещенко", 176, 74 },
	{ "Дмитрий", "Комбаров", 182, 76 },
	{ "Лукас", "Фернандо", 175, 80 },
	{ "Денис", "Глушаков", 182, 82 },
	{ "Квинси", "Промес", 174, 71 },
	{ "Джано", "Ананидзе", 172, 64 },
	{ "Зе", "Луиш", 184, 84 },
};

bool LessHeight(const SSportsman &lhs, const SSportsman & rhs) {
	return lhs.height < rhs.height ? true : false;
};

BOOST_AUTO_TEST_SUITE(Template_function_FindMaxEx)
	
	BOOST_AUTO_TEST_SUITE(return_false_if_vector_is_empty)
	
		BOOST_AUTO_TEST_CASE(and_do_not_modify_max_value){
			SSportsman initialSportsman, testSportsman;
			BOOST_CHECK(!FindMaxEx(emptyVector, testSportsman, LessHeight));
			CheckSportsmansEquality(initialSportsman, testSportsman);
		}
	
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(return_true_for_nonempty_vector)

		BOOST_AUTO_TEST_SUITE(and_give_right_value)

			BOOST_AUTO_TEST_CASE(if_use_function){
				SSportsman initialSportsman, testSportsman;
				BOOST_CHECK(FindMaxEx(team, testSportsman, LessHeight));
				CheckSportsmansEquality(keeper, testSportsman);
			}
			BOOST_AUTO_TEST_CASE(if_use_lambda) {
				SSportsman initialSportsman, testSportsman;
				BOOST_CHECK(FindMaxEx(team, testSportsman, [](const auto &lhs, const auto & rhs) {
					return lhs.weight < rhs.weight ? true : false;
				}));
				CheckSportsmansEquality(keeper, testSportsman);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


