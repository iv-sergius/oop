#include "stdafx.h"
#include "../Car.h"

/*
Car is turn off by default
*/

struct CarFixture
{
	CCar car;
};
// Car
BOOST_FIXTURE_TEST_SUITE(Test_Car_class, CarFixture)

	BOOST_AUTO_TEST_CASE(engine_is_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsEngineTurnedOn());
	}
	BOOST_AUTO_TEST_CASE(can_not_select_gear_when_engine_is_turned_off)
	{
		BOOST_CHECK_EQUAL(car.SetGear(1), false);
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}
	BOOST_AUTO_TEST_CASE(can_not_select_speed_when_engine_is_turned_off)
	{
		BOOST_CHECK_EQUAL(car.SetSpeed(1), false);
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

	BOOST_AUTO_TEST_SUITE(Try_turn_on_engine)

		BOOST_AUTO_TEST_CASE(after_this_gear_is_neutral_and_speed_is_0)
		{
			car.TurnOnEngine();
			BOOST_CHECK_EQUAL(car.GetGear(), 0);
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_turned_on_ : CarFixture
	{
		when_turned_on_()
		{
			car.TurnOnEngine();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(When_engine_is_turned_on, when_turned_on_)

		BOOST_AUTO_TEST_SUITE(Try_turn_off_engine)

			BOOST_AUTO_TEST_CASE(can_not_if_gear_is_not_neutral)
			{
				car.SetGear(1);
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), true);
				BOOST_CHECK_EQUAL(car.TurnOffEngine(), false);
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), true);
			}
			BOOST_AUTO_TEST_CASE(can_not_if_speed_is_not_0)
			{
				car.SetGear(1);
				car.SetSpeed(1);
				car.SetGear(0);
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), true);
				BOOST_CHECK_EQUAL(car.TurnOffEngine(), false);
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), true);
			}
			BOOST_AUTO_TEST_CASE(can_if_gear_is_neutral_and_speed_is_0)
			{
				BOOST_CHECK_EQUAL(car.GetGear(), 0);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
				BOOST_CHECK_EQUAL(car.TurnOffEngine(), true);
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), false);
			}
			BOOST_AUTO_TEST_CASE(after_turn_off_gear_is_neutral_and_speed_is_0)
			{
				BOOST_CHECK_EQUAL(car.TurnOffEngine(), true);
				BOOST_CHECK_EQUAL(car.GetGear(), 0);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(Check_range_of_each_gear)
			BOOST_AUTO_TEST_CASE(check_1_gear)
			{
				car.SetGear(1);
				car.SetSpeed(1);
				BOOST_CHECK_EQUAL(car.SetSpeed(0), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
				BOOST_CHECK_EQUAL(car.SetSpeed(-1), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
				BOOST_CHECK_EQUAL(car.SetSpeed(30), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
				BOOST_CHECK_EQUAL(car.SetSpeed(31), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
			}
			BOOST_AUTO_TEST_CASE(check_2_gear)
			{
				car.SetGear(2);
				BOOST_CHECK_EQUAL(car.SetSpeed(20), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
				BOOST_CHECK_EQUAL(car.SetSpeed(19), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
				BOOST_CHECK_EQUAL(car.SetSpeed(50), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
				BOOST_CHECK_EQUAL(car.SetSpeed(51), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
			}
			BOOST_AUTO_TEST_CASE(check_3_gear)
			{
				car.SetGear(3);
				BOOST_CHECK_EQUAL(car.SetSpeed(30), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
				BOOST_CHECK_EQUAL(car.SetSpeed(29), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
				BOOST_CHECK_EQUAL(car.SetSpeed(60), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 60);
				BOOST_CHECK_EQUAL(car.SetSpeed(61), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 60);
			}
			BOOST_AUTO_TEST_CASE(check_4_gear)
			{
				car.SetGear(4);
				BOOST_CHECK_EQUAL(car.SetSpeed(40), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 40);
				BOOST_CHECK_EQUAL(car.SetSpeed(39), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 40);
				BOOST_CHECK_EQUAL(car.SetSpeed(90), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 90);
				BOOST_CHECK_EQUAL(car.SetSpeed(91), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 90);
			}
			BOOST_AUTO_TEST_CASE(check_5_gear)
			{
				car.SetGear(5);
				BOOST_CHECK_EQUAL(car.SetSpeed(50), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
				BOOST_CHECK_EQUAL(car.SetSpeed(49), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
				BOOST_CHECK_EQUAL(car.SetSpeed(150), true);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 150);
				BOOST_CHECK_EQUAL(car.SetSpeed(151), false);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 150);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()