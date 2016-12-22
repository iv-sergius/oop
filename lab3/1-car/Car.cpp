#include "stdafx.h"
#include "Car.h"
#include <cmath>

namespace
{

const std::map<CCar::CarGear, CCar::SLimits> GEAR_LIMITS = {
	{ CCar::CarGear::Reverse, { 0,   20 } },
	{ CCar::CarGear::Neutral, { 0,  150 } },
	{ CCar::CarGear::First,   { 0,   30 } },
	{ CCar::CarGear::Second,  { 20,  50 } },
	{ CCar::CarGear::Third,   { 30,  60 } },
	{ CCar::CarGear::Fourth,  { 40,  90 } },
	{ CCar::CarGear::Fifth,   { 50, 150 } }
};

}

CCar::CCar() 
	: m_gearLimits(GEAR_LIMITS)
{

}

bool CCar::TurnOnEngine()
{
	m_isTurnOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_speed == 0 && m_gear == Neutral)
	{
		m_isTurnOn = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool CCar::SetGear(int gear)
{
	CarGear carGear = static_cast <CarGear>(gear);
	if (m_isTurnOn && IsSpeedInGearLimits(carGear, m_speed))
	{
		m_gear = carGear;
		return true;
	}
	else
	{
		return false;
	}
}

bool CCar::SetSpeed(unsigned speed)
{
	if (IsSpeedInGearLimits(m_gear, speed))
	{
		if (m_gear == CarGear::Reverse)
		{
			m_speed = - static_cast<int>(speed);
		}
		else if (m_gear == CarGear::Neutral)
		{
			m_speed = speed;
		}
		else
		{
			m_speed = speed;
		}
		return true;
	}
	return false;
}

bool CCar::IsEngineTurnedOn() const
{
	return m_isTurnOn;
}

int CCar::GetGear() const
{
	return static_cast<int>(m_gear);
}

unsigned CCar::GetSpeed() const
{
	return abs(m_speed);
}

bool CCar::IsSpeedInGearLimits(CarGear gear, int speed)
{
	if (gear == CarGear::Neutral)
	{
		return abs(speed) <= abs(m_speed);
	}
	else
	{
		return speed >= m_gearLimits.at(gear).min && speed <= m_gearLimits.at(gear).max;
	}
}

