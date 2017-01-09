#pragma once
#include "stdafx.h"

class IShape
{
public:
	virtual ~IShape() {};
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	std::string GetOutlineColor() const;
private:
	std::string m_outlineColor = "00000";
protected:
	void SetOutlineColor(const std::string &stringColor);
};