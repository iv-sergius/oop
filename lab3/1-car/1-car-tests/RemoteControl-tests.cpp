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
	BOOST_AUTO_TEST_CASE(handle_false_on_unknown_command)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << "TurnOn");
		BOOST_CHECK(!remoteControl.HandleCommand());
	}
	BOOST_AUTO_TEST_CASE(EngineOn_command_can_turn_on)
	{
		VerifyCommandHandling("EngineOn", true, 0, 0, "Car's engine is turned on\n");
	}
	BOOST_AUTO_TEST_SUITE(EngineOff_command_can)
		BOOST_AUTO_TEST_CASE(turn_off)
		{
			car.TurnOnEngine();
			VerifyCommandHandling("EngineOff", false, 0, 0, "Car's engine is turned off\n");
		}
		BOOST_AUTO_TEST_CASE(say_about_error)
		{
			car.TurnOnEngine();
			car.SetGear(1);
			VerifyCommandHandling("EngineOff", true, 1, 0, "To turn off need Neutral gear and speed 0\n");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(Info_print_car_info)
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(19);
		VerifyCommandHandling("Info", true, 1, 19, "Car's engine is turn on. Gear is 1, Speed is 19\n");
	}

	BOOST_AUTO_TEST_SUITE(SetGear_command_can)
		BOOST_AUTO_TEST_CASE(set_gear)
		{
			car.TurnOnEngine();
			VerifyCommandHandling("SetGear 1", true, 1, 0, "Gear set to 1\n");
		}
		BOOST_AUTO_TEST_CASE(say_what_need_number)
		{
			car.TurnOnEngine();
			VerifyCommandHandling("SetGear a", true, 0, 0, "Gear must be a number\n");
		}
		BOOST_AUTO_TEST_CASE(say_what_engine_must_be_turn_on_before)
		{
			VerifyCommandHandling("SetGear 1", false, 0, 0, "Can't set gear then engine is turn off\n");
		}
		BOOST_AUTO_TEST_CASE(say_about_unavailable_gear)
		{
			car.TurnOnEngine();
			VerifyCommandHandling("SetGear -2", true, 0, 0, "This gear is unavailable on this car\n");
		}
		BOOST_AUTO_TEST_CASE(say_about_incompatible_speed)
		{
			car.TurnOnEngine();
			VerifyCommandHandling("SetGear 2", true, 0, 0, "Can't set gear on this speed\n");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(SetSpeed_command_can)
		BOOST_AUTO_TEST_CASE(set_speed)
		{
			car.TurnOnEngine();
			car.SetGear(1);
			VerifyCommandHandling("SetSpeed 19", true, 1, 19, "Speed set to 19\n");
		}
		BOOST_AUTO_TEST_CASE(say_what_need_number)
		{
			car.TurnOnEngine();
			car.SetGear(1);
			VerifyCommandHandling("SetSpeed a", true, 1, 0, "Speed must be a number\n");
		}
		BOOST_AUTO_TEST_CASE(say_what_engine_must_be_turn_on_before)
		{
			VerifyCommandHandling("SetSpeed 19", false, 0, 0, "Can't set speed then engine is turn off\n");
		}
		BOOST_AUTO_TEST_CASE(say_about_incompatible_speed)
		{
			car.TurnOnEngine();
			car.SetGear(1);
			VerifyCommandHandling("SetSpeed 31", true, 1, 0, "Speed lie out of gear limits\n");
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()