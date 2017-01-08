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
	void EngineOn(std::istream & args);
	void EngineOff(std::istream & args);
	void Info(std::istream & args);
	void SetGear(std::istream & args);
	void SetSpeed(std::istream & args);
private:
	typedef std::map<std::string, std::function<void(std::istream & args)>> ActionMap;

	CCar & m_car;
	std::istream & m_input;
	std::ostream & m_output;

	const ActionMap m_actionMap;
};

