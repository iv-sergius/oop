#pragma once
#include "stdafx.h"
#include "Shape.h"
#include "Point.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(const CPoint &point1, const CPoint &point2, const std::string &outlineColor);
	double GetArea() const ;
	double GetPerimeter() const ;
	std::string ToString() const ;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
};