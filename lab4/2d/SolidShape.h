#pragma once
#include "stdafx.h"
#include "Shape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() {};
	virtual std::string GetFillColor() const = 0;
protected:
private:
};

class CSolidShape : public ISolidShape, public CShape
{
public:
	CSolidShape(const std::string & typeName, const std::string & outlineColor, const std::string & fillColor);
	std::string GetFillColor() const final;
	std::string GetOutlineColor() const final;
	std::string ToString() const final;
protected:
	void AppendProperties(std::ostream & strm) const;
private:
	std::string m_fillColor;
};

