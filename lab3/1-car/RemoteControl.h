#pragma once
#include <boost/noncopyable.hpp>

class CCar;

// Наследование от boost::noncopyable - явный способ запретить копирование и присваивание экземпляров класса
class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CCar & car, std::istream & input, std::ostream & output);
	bool HandleCommand();

	// Избавляемся от предупреждения компилятора о том, что он не сможет сгенерировать оператор присваивания
	// CRemoteControl& operator=(const CRemoteControl &) = delete;
private:
	bool EngineOn(std::istream & args);
	bool EngineOff(std::istream & args);
	bool Info(std::istream & args);
	bool SetGear(std::istream & args);
	bool SetSpeed(std::istream & args);
private:
	typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;

	CCar & m_car;
	std::istream & m_input;
	std::ostream & m_output;

	const ActionMap m_actionMap;
};

