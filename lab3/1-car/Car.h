#pragma once



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
	bool IsSpeedInGearLimits(CarGear gear, int speed);
protected:
	bool m_isTurnOn = false;
	CarGear m_gear = CarGear::Neutral;
	int m_speed = 0;
};

