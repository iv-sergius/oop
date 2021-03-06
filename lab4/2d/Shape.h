#pragma once
#include "stdafx.h"

class IShape
{
public:
	IShape() = default;
	virtual ~IShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual std::string GetOutlineColor() const = 0;
protected:
	virtual void AppendProperties(std::ostream & strm) const = 0;
private:
};

class CShape : virtual public IShape
{
public:
	CShape(const std::string & typeName, const std::string & outlineColor);
	virtual ~CShape() = default;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;
protected:
private:
	std::string m_outlineColor = "00000";
	std::string m_typeName;
};

std::string NormalizeColor(const std::string &stringColor);