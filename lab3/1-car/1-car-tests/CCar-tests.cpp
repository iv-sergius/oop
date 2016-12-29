#include "stdafx.h"
#include "../Car.h"
#include <boost\test\unit_test.hpp>

void CheckGearLimits(CCar & car, const int gear, const int minSpeed, const int maxSpeed)
{
	for (int i = 1; i < gear; ++i)
	{
		car.SetGear(i);
		car.SetSpeed(minSpeed * (i + 1) / gear );
	}
	//car.SetGear(gear);
	car.SetGear(gear);
	BOOST_CHECK_EQUAL(car.GetGear(), gear);
	car.SetSpeed(minSpeed);
	BOOST_CHECK_EQUAL(car.GetSpeed(), minSpeed);
	BOOST_REQUIRE_THROW(car.SetSpeed(minSpeed - 1), std::out_of_range);
	BOOST_CHECK_EQUAL(car.GetSpeed(), minSpeed);
	car.SetSpeed(maxSpeed);
	BOOST_CHECK_EQUAL(car.GetSpeed(), maxSpeed);
	BOOST_REQUIRE_THROW(car.SetSpeed(maxSpeed + 1), std::out_of_range);
	BOOST_CHECK_EQUAL(car.GetSpeed(), maxSpeed);
}

void CheckEnableGearMinSpeed(CCar & car, const int gear, const int minSpeed)
{
	for (int i = 1; i < gear; ++i)
	{
		car.SetGear(i);
		car.SetSpeed(minSpeed * (i + 1) / gear);
	}
	car.SetGear(gear - 1);
	BOOST_CHECK_EQUAL(car.GetGear(), gear - 1);
	car.SetSpeed(minSpeed - 1);
	BOOST_CHECK_EQUAL(car.GetSpeed(), minSpeed - 1);
	BOOST_REQUIRE_THROW(car.SetGear(gear), std::out_of_range);
	BOOST_CHECK_EQUAL(car.GetGear(), gear - 1);
	BOOST_CHECK_EQUAL(car.GetSpeed(), minSpeed - 1);
	car.SetSpeed(minSpeed);
	BOOST_CHECK_EQUAL(car.GetSpeed(), minSpeed);
	car.SetGear(gear); // cool
	BOOST_CHECK_EQUAL(car.GetGear(), gear);
	BOOST_CHECK_EQUAL(car.GetSpeed(), minSpeed);
}

void CheckEnableGearMaxSpeed(CCar & car, const int gear, const int maxSpeed)
{
	if (gear < MAX_GEAR)
	{
		car.SetGear(gear);
		car.SetSpeed(maxSpeed);
		car.SetGear(gear + 1);
		BOOST_CHECK_EQUAL(car.GetGear(), gear + 1);
		car.SetSpeed(maxSpeed + 1);
		BOOST_CHECK_EQUAL(car.GetSpeed(), maxSpeed + 1);
		BOOST_REQUIRE_THROW(car.SetGear(gear), std::out_of_range);
		BOOST_CHECK_EQUAL(car.GetGear(), gear + 1);
		BOOST_CHECK_EQUAL(car.GetSpeed(), maxSpeed + 1);
	
		car.SetSpeed(maxSpeed);
		BOOST_CHECK_EQUAL(car.GetSpeed(), maxSpeed);
		car.SetGear(gear); // cool
		BOOST_CHECK_EQUAL(car.GetGear(), gear);
		BOOST_CHECK_EQUAL(car.GetSpeed(), maxSpeed);
	}
}

void CheckEnableGearSpeed(CCar & car, const int gear, const int minSpeed, const int maxSpeed)
{
	if (gear > 1)
	{
		CheckEnableGearMinSpeed(car, gear, minSpeed);
	}
	if (gear < MAX_GEAR)
	{
		CheckEnableGearMaxSpeed(car, gear, maxSpeed);
	}
}

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
		BOOST_REQUIRE_THROW(car.SetSpeed(1), std::out_of_range);
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}
	BOOST_AUTO_TEST_CASE(can_not_select_speed_when_engine_is_turned_off)
	{
		BOOST_REQUIRE_THROW(car.SetSpeed(1), std::out_of_range);
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
				BOOST_REQUIRE_THROW(car.TurnOffEngine(), std::out_of_range);
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), true);
			}
			BOOST_AUTO_TEST_CASE(can_not_if_speed_is_not_0)
			{
				car.SetGear(1);
				car.SetSpeed(1);
				car.SetGear(0);
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), true);
				BOOST_REQUIRE_THROW(car.TurnOffEngine(), std::out_of_range);
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), true);
			}
			BOOST_AUTO_TEST_CASE(can_if_gear_is_neutral_and_speed_is_0)
			{
				BOOST_CHECK_EQUAL(car.GetGear(), 0);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
				//BOOST_CHECK_EQUAL(car.TurnOffEngine(), true);
				car.TurnOffEngine();
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), false);
			}
			BOOST_AUTO_TEST_CASE(after_turn_off_gear_is_neutral_and_speed_is_0)
			{
				//BOOST_CHECK_EQUAL(car.TurnOffEngine(), true);
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), true);
				car.TurnOffEngine();
				BOOST_CHECK_EQUAL(car.IsEngineTurnedOn(), false);
				BOOST_CHECK_EQUAL(car.GetGear(), 0);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(Check_avalible_speed_range)
			BOOST_AUTO_TEST_CASE(reverse_gear)
			{
				CheckGearLimits(car, -1, 0, 20);
			}
			BOOST_AUTO_TEST_CASE(neutral_gear)
			{
				car.SetGear(1);
				car.SetSpeed(10);
				car.SetGear(0);
				BOOST_CHECK_EQUAL(car.GetGear(), 0);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 10);
				BOOST_REQUIRE_THROW(car.SetSpeed(11), std::out_of_range); //
				BOOST_CHECK_EQUAL(car.GetSpeed(), 10);
				car.SetSpeed(9);
				BOOST_CHECK_EQUAL(car.GetSpeed(), 9);
			}
			BOOST_AUTO_TEST_CASE(for_1_gear)
			{
				CheckGearLimits(car, 1, 0, 30);
			}
			BOOST_AUTO_TEST_CASE(for_2_gear)
			{
				CheckGearLimits(car, 2, 20, 50);
			}
			BOOST_AUTO_TEST_CASE(for_3_gear)
			{
				CheckGearLimits(car, 3, 30, 60);
			}
			BOOST_AUTO_TEST_CASE(for_4_gear)
			{
				CheckGearLimits(car, 4, 40, 90);
			}
			BOOST_AUTO_TEST_CASE(for_5_gear)
			{
				CheckGearLimits(car, 5, 50, 150);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(Check_speed_range_that)
			BOOST_AUTO_TEST_SUITE(enable_reverse_gear)
				BOOST_AUTO_TEST_CASE(from_Neutral_gear)
				{
					car.SetGear(1);
					car.SetSpeed(1);
					car.SetGear(0);
					BOOST_CHECK_EQUAL(car.GetGear(), 0);
					BOOST_CHECK_EQUAL(car.GetSpeed(), 1);
					BOOST_REQUIRE_THROW(car.SetGear(-1), std::out_of_range);
					car.SetSpeed(0);
					BOOST_CHECK_EQUAL(car.GetGear(), 0);
					car.SetGear(-1);
					BOOST_CHECK_EQUAL(car.GetGear(), -1);
				}
				BOOST_AUTO_TEST_CASE(from_1_gear)
				{
					car.SetGear(1);
					car.SetSpeed(1);
					BOOST_CHECK_EQUAL(car.GetGear(), 1);
					BOOST_CHECK_EQUAL(car.GetSpeed(), 1);
					BOOST_REQUIRE_THROW(car.SetGear(-1), std::out_of_range);
					car.SetSpeed(0);
					BOOST_CHECK_EQUAL(car.GetGear(), 0);
					car.SetGear(-1);
					BOOST_CHECK_EQUAL(car.GetGear(), -1);
				}
			BOOST_AUTO_TEST_SUITE_END()
			BOOST_AUTO_TEST_CASE(enable_1_gear)
			{
				CheckEnableGearSpeed(car, 1, 0, 30);
			}
			BOOST_AUTO_TEST_CASE(enable_2_gear)
			{
				CheckEnableGearSpeed(car, 2, 20, 50);
			}
			BOOST_AUTO_TEST_CASE(enable_3_gear)
			{
				CheckEnableGearSpeed(car, 3, 30, 60);
			}
			BOOST_AUTO_TEST_CASE(enable_4_gear)
			{
				CheckEnableGearSpeed(car, 4, 40, 90);
			}
			BOOST_AUTO_TEST_CASE(enable_5_gear)
			{
				CheckEnableGearSpeed(car, 5, 50, 150);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()