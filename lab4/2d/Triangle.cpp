#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(const CPoint & vertex1, const CPoint & vertex2, const CPoint & vertex3, const std::string & outlineColor, const std::string & fillColor)
	: CSolidShape("Triangle", outlineColor, fillColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

double CTriangle::GetArea() const
{
	return 0.5 * abs((m_vertex1.x - m_vertex3.x) *(m_vertex2.y - m_vertex3.y) - (m_vertex2.x - m_vertex3.x) * (m_vertex1.y - m_vertex3.y));
}

double CTriangle::GetPerimeter() const
{
	return Distance(m_vertex1, m_vertex2) + Distance(m_vertex2, m_vertex3) + Distance(m_vertex1, m_vertex3);
}

std::string CTriangle::ToString() const
{
	return std::string();
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
