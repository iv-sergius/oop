#include "stdafx.h"
#include "SolidShape.h"
#include "Point.h"

#define _USE_MATH_DEFINES
#include <math.h>

class CCircle : public CSolidShape
{
public:
	CCircle(const CPoint & center, double radius, const std::string &outlineColor, const std::string &fillColor);
	
	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;

	CPoint GetCenter() const;
	double GetRadius() const;
private:
	CPoint m_center;
	double m_radius;
};