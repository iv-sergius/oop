#pragma once
#include <map>

static const int MAX_GEAR =  5;
static const int MIN_GEAR = -1;

class CCar
{
public:
	enum CarGear {
		Reverse	= -1,
		Neutral	= 0,
		First	= 1,
		Second	= 2,
		Third	= 3,
		Fourth	= 4,
		Fifth	= 5
	};

	CCar() = default;
	~CCar() = default;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(unsigned speed);
	bool IsEngineTurnedOn()const;
	int GetGear()const;
	unsigned GetSpeed()const;
private:
	struct SLimits
	{
		int min;
		int max;
	};
	const std::map<CarGear, SLimits> gearLimits = {
		{CarGear::Reverse, { 0,  20}},
		{CarGear::Neutral, { 0, 150}},
		{CarGear::First,   { 0,  30}},
		{CarGear::Second,  {20,  50}},
		{CarGear::Third,   {30,  60}},
		{CarGear::Fourth,  {40,  90}},
		{CarGear::Fifth,   {50, 150}}
	};
	bool IsSpeedInGearLimits(CarGear gear, int speed);
protected:
	bool m_isTurnOn = false;
	CarGear m_gear = CarGear::Neutral;
	int m_speed = 0;
};

