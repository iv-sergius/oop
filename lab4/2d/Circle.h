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

	CPoint GetCenter() const;
	double GetRadius() const;
protected:
	void AppendProperties(std::ostream & strm) const;
private:
	CPoint m_center;
	double m_radius;
};