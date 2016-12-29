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

void CCar::TurnOnEngine()
{
	m_isTurnOn = true;
}

void CCar::TurnOffEngine()
{
	if (m_speed == 0 && m_gear == Neutral)
	{
		m_isTurnOn = false;
	}
	else
	{
		throw std::out_of_range("To turn off need 0 speed on Neutral\n");
	}
}

void CCar::SetGear(int gear)
{
	if (!m_isTurnOn)
	{
		throw std::out_of_range("Can't set gear then engine is turn off\n");
	}
	CarGear newGear = static_cast <CarGear>(gear);
	if (!IsSpeedInGearLimits(newGear, m_speed))
	{
		throw std::out_of_range("Can't set gear on this speed\n");
	}
	if (newGear != CarGear::Reverse)
	{
		m_gear = newGear;
	}
	else
	{
		if ((m_gear == CarGear::Neutral || m_gear == CarGear::First) && m_speed == 0)
		{
			m_gear = newGear;
		}
		else
		{
			throw std::out_of_range("Reverse gear avalibe only on 0 speed and from Neutral or Reverse gear\n");
		}
	}

}

void CCar::SetSpeed(unsigned speed)
{
	if (IsSpeedInGearLimits(m_gear, speed))
	{
		if (m_gear == CarGear::Reverse)
		{
			m_speed = - static_cast<int>(speed);
		}
		else if (m_gear == CarGear::Neutral)
		{
			if (speed <= abs(m_speed))
			{
				m_speed = speed;
			}
			else
			{
				throw std::out_of_range("Can't to speed up on Neutral gear");
			}
		}
		else
		{
			m_speed = speed;
		}
	}
	else
	{
		throw std::out_of_range("Speed lie out of gear limits");
	}
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
	return speed >= m_gearLimits.at(gear).min && speed <= m_gearLimits.at(gear).max;
}

