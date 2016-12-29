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
	CCar();
	~CCar() = default;
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(unsigned speed);
	bool IsEngineTurnedOn()const;
	int GetGear()const;
	unsigned GetSpeed()const;
	struct SLimits
	{
		int min;
		int max;
	};
private:
	const std::map<CarGear, SLimits> m_gearLimits;
	bool IsSpeedInGearLimits(CarGear gear, int speed);
protected:
	bool m_isTurnOn = false;
	CarGear m_gear = CarGear::Neutral;
	int m_speed = 0;
};

