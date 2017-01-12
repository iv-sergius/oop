#include "stdafx.h"
#include "Circle.h"

CCircle::CCircle(const CPoint & center, double radius, const std::string & outlineColor, const std::string & fillColor)
	: CSolidShape("Circle", outlineColor, fillColor)
	, m_center(center)
{
	if (radius >= 0.)
	{
		m_radius = radius;
	}
	else
	{
		throw std::invalid_argument("Circle radius must be non negative");
	}
}

double CCircle::GetArea() const
{
	return m_radius * m_radius * M_PI;
}

double CCircle::GetPerimeter() const
{
	return 2. * m_radius * M_PI;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::AppendProperties(std::ostream & strm) const
{
	strm << "\tcenter point = " << m_center.ToString() << std::endl
		<< "\tradius = " << m_radius << std::endl;
	CSolidShape::AppendProperties(strm);
}
