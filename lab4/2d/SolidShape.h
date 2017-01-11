#pragma once
#include "stdafx.h"
#include "Shape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() {};
//	virtual double GetArea() const = 0;
//	virtual double GetPerimeter() const = 0;
//	virtual std::string ToString() const = 0;
	virtual std::string GetFillColor() const = 0;
protected:
private:
};

class CSolidShape : public ISolidShape, public CShape
{
public:
	CSolidShape(const std::string & typeName, const std::string & outlineColor, const std::string & fillColor);
	std::string GetFillColor() const;
	std::string GetOutlineColor() const;
protected:
private:
	std::string m_fillColor;
};

