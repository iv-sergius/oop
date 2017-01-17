#pragma once
#include "stdafx.h"
#include "Shape.h"

class ISolidShape : virtual public IShape
{
public:
	ISolidShape() = default;
	virtual ~ISolidShape() = default;
	virtual std::string GetFillColor() const = 0;
protected:
private:
};

class CSolidShape : public CShape, public ISolidShape
{
public:
	CSolidShape(const std::string & typeName, const std::string & outlineColor, const std::string & fillColor);
	virtual ~CSolidShape() = default;
	std::string GetFillColor() const override final;
	std::string GetOutlineColor() const override final;
	std::string ToString() const override;
protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	std::string m_fillColor;
};

