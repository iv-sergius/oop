#include "stdafx.h"
#include "Line.h"

CLineSegment::CLineSegment(const CPoint & point1, const CPoint & point2, const std::string & outlineColor)
	: CShape("LineSegment", outlineColor)
	, m_vertex1(point1)
	, m_vertex2(point2)
{
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_vertex1;
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

void CLineSegment::AppendProperties(std::ostream & strm) const
{
	strm << "\tstart point = " << m_vertex1.ToString() << std::endl
		<< "\tend point = " << m_vertex2.ToString() <<std::endl;
}

