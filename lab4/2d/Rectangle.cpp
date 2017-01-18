#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(const CPoint & leftTop, const CPoint & rightBottom, const std::string & outlineColor, const std::string & fillColor)
	: CSolidShape("Rectangle", outlineColor, fillColor)
	, m_leftTop(leftTop)
{
	if (leftTop.x > rightBottom.x || leftTop.y > rightBottom.y)
	{
		throw std::invalid_argument("Each coordinat of leftTop must be less or equal of rightBottom's corresponding coordinat");
	}
	else
	{
		m_rightBottom = rightBottom;
	}
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
	return 2. * (GetWidth() + GetHeight());
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double CRectangle::GetWidth() const
{
	return m_rightBottom.x - m_leftTop.x;
}

double CRectangle::GetHeight() const
{
	return m_rightBottom.y - m_leftTop.y;
}

void CRectangle::AppendSolidShapeProperties(std::ostream & strm) const
{
	strm << "\tleft top point = " << m_leftTop.ToString() << std::endl
		<< "\tright bottom point = " << m_rightBottom.ToString() << std::endl;
}