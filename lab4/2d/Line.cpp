#include "stdafx.h"
#include "Line.h"

CLineSegment::CLineSegment(const CPoint & point1, const CPoint & point2, const std::string & outlineColor)
	: m_vertex1(point1)
	, m_vertex2(point2)
{
	SetOutlineColor(outlineColor);
}

CPoint CLineSegment::GetStartPoint() const
{
	return CPoint();
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_vertex2;
}

double CLineSegment::GetPerimeter() const
{
	return Distance(m_vertex1, m_vertex2);
}

double CLineSegment::GetArea() const
{
	return 0.;
}

std::string CLineSegment::ToString() const
{
	return "";
}
