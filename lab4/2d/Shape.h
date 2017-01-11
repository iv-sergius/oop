#pragma once
#include "stdafx.h"

class IShape
{
public:
	virtual ~IShape() {};
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual std::string GetOutlineColor() const = 0;
protected:
private:
};

class CShape : public IShape
{
public:
	CShape(const std::string & typeName, const std::string & outlineColor);
	std::string GetOutlineColor() const;
protected:
private:
	std::string m_outlineColor = "00000";
	std::string m_typeName;
};

std::string NormalizeColor(const std::string &stringColor);