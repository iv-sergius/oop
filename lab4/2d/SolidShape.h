#pragma once
#include "stdafx.h"
#include "Shape.h"

class ISolidShape : public IShape
{
public:
	std::string GetFillColor() const;
private:
	std::string m_fillColor;
};

