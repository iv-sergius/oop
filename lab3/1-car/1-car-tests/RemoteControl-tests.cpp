#include "stdafx.h"
#include "../RemoteControl.h"
#include "../Car.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

// Зависимости RemoteControl-а вынесены в родительскую структуру,
// чтобы гарантировать их создание до конструирования самого remote-контрола
struct RemoteControlDependencies
{
	CCar car;
	stringstream input;
	stringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;
	
	RemoteControlFixture()
		: remoteControl(car, input, output)
	{
	}

	// Вспомогательная функция для проверки работы команды command
	// Она принимает ожидаемый номер канала expectedChannel и expectedOutput
	void VerifyCommandHandling(
		const string& command, 
		const bool expectedIsTurnOn, 
		const int expectedGear, 
		const unsigned int expectedSpeed, 
		const string& expectedOutput)
	{
		// Предварительно очищаем содержимое выходного потока
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), expectedIsTurnOn);
		BOOST_CHECK_EQUAL(car.GetGear(), expectedGear);
		BOOST_CHECK_EQUAL(car.GetSpeed(), expectedSpeed);
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)

	BOOST_AUTO_TEST_CASE(EngineOn_command_turn_on)
	{
		VerifyCommandHandling("EngineOn", true, 0, 0, "Car's engine is turned on\n");
	}

	BOOST_AUTO_TEST_CASE(EngineOoff_command_turn_off)
	{
		car.TurnOnEngine();
		VerifyCommandHandling("EngineOff", false, 0, 0, "Car's engine is turned off\n");
	}


	// Раскомментируйте тест, проверяющий работу команды Info
	// Убедитесь, что он не проходит (т.к. в CRemoteControl отсутствует требуемый функционал)
	// Доработайте простейшим образом класс CRemoteControl, чтобы этот тест и предыдущие проходили
	// При необходимости выполните рефакторинг кода, сохраняя работоспособность тестов
	BOOST_AUTO_TEST_CASE(Info_print_car_info)
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(19);
		VerifyCommandHandling("Info", true, 1, 19, "Car's engine is turn on. Gear is 1, Speed is 19\n");
	}


/*
	// Раскомментируйте тест, проверяющий работу команды SelectChannel 
	//	попытке при выбрать доступный номер канала у включенного телевизора
	// Убедитесь, что он не проходит (т.к. в CRemoteControl отсутствует требуемый функционал)
	// Доработайте простейшим образом класс CRemoteControl, чтобы этот тест и предыдущие проходили
	// При необходимости выполните рефакторинг кода, сохраняя работоспособность тестов
	BOOST_AUTO_TEST_CASE(can_select_a_valid_channel_when_tv_which_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("SelectChannel 42", 42, "Channel selected\n");
	}
*/

/*
	// Раскомментируйте тест, проверяющий работу команды SelectChannel 
	//	попытке при выбрать доступный либо недоступный номер канала у выключенного телевизора
	// Убедитесь, что он не проходит (т.к. в CRemoteControl отсутствует требуемый функционал)
	// Доработайте простейшим образом класс CRemoteControl, чтобы этот тест и предыдущие проходили
	// При необходимости выполните рефакторинг кода, сохраняя работоспособность тестов
	BOOST_AUTO_TEST_CASE(cant_select_channel_when_tv_is_turned_off)
	{
		VerifyCommandHandling("SelectChannel 42", none, "Can't select channel because TV is turned off\n");
		VerifyCommandHandling("SelectChannel 100", none, "Can't select channel because TV is turned off\n");
	}
*/

/*
	// Раскомментируйте тест, проверяющий работу команды SelectChannel 
	//	попытке при выбрать недоступный номер канала у включенного телевизора
	// Убедитесь, что он не проходит (т.к. в CRemoteControl отсутствует требуемый функционал)
	// Доработайте простейшим образом класс CRemoteControl, чтобы этот тест и предыдущие проходили
	// При необходимости выполните рефакторинг кода, сохраняя работоспособность тестов
	BOOST_AUTO_TEST_CASE(cant_select_an_invalid_channel_when_tv_is_on)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("SelectChannel 100", 42, "Invalid channel\n");
		VerifyCommandHandling("SelectChannel 0", 42, "Invalid channel\n");
	}
*/

	// Напишите тесты для недостающего функционала класса CRemoteControl (если нужно)
	//	и для дополнительных заданий на бонусные баллы (если нужно)
	// После написания каждого теста убедитесь, что он не проходит.
	// Доработайте простейшим образом класс CRemoteControl, чтобы этот тест и предыдущие проходили
	// При необходимости выполните рефакторинг кода, сохраняя работоспособность тестов
	// При необходимости используйте вложенные тесты (как использующие fixture, так и нет)
	// Имена тестам и test suite-ам давайте такие, чтобы выводимая в output иерархия
	//	тестов читалась как спецификация на английском языке, описывающая поведение remote control-а

BOOST_AUTO_TEST_SUITE_END()