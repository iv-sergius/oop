#include "stdafx.h"
#include "RemoteControl.h"
#include "Car.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CCar & car, std::istream & input, std::ostream & output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "EngineOn", [this](istream & strm) {
				return EngineOn(strm);
			} },
		{ "EngineOff", bind(&CRemoteControl::EngineOff, this, _1) },
		{ "Info", bind(&CRemoteControl::Info, this, _1) },
		{ "SetGear", bind(&CRemoteControl::SetGear, this, _1) },
		{ "SetSpeed", bind(&CRemoteControl::SetSpeed, this, _1) }
	})
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	
	return false;
}

bool CRemoteControl::EngineOn(std::istream & /*args*/)
{
	m_car.TurnOnEngine();
	m_output << "Car's engine is turned on" << endl;
	return true;
}

bool CRemoteControl::EngineOff(std::istream & /*args*/)
{
	m_car.TurnOffEngine();
	m_output << "Car's engine is turned off" << endl;
	return true;
}

bool CRemoteControl::Info(std::istream & /*args*/)
{
	string info = (m_car.IsEngineTurnedOn()) ? "Car's engine is turn on." : "Car's engine is turn off.";
	info += " Gear is " + to_string(m_car.GetGear()) + ", Speed is " + to_string(m_car.GetSpeed());
	m_output << info << std::endl;
	return true;
}

bool CRemoteControl::SetGear(std::istream & arg)
{
	int gear;
	if (!(arg >> gear))
	{
		m_output << "Gear must be a number" << std::endl;
		return false;
	}
	try 
	{
		m_car.SetGear(gear);
		m_output << "Gear set to " << gear << std::endl;
	}
	catch (const std::out_of_range &e) 
	{
		m_output << e.what() << std::endl;
	}
	return true;
}

bool CRemoteControl::SetSpeed(std::istream & arg)
{
	unsigned int speed;
	if (!(arg >> speed))
	{
		m_output << "Speed must be a number" << std::endl;
		return false;
	}
	try
	{
		m_car.SetSpeed(speed);
		m_output << "Speed set to " << speed << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		m_output << e.what() << std::endl;
	}
	return true;
}