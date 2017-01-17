#pragma once
#include "stdafx.h"
#include "Shape.h"
#include "Point.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(const CPoint &point1, const CPoint &point2, const std::string &outlineColor);
	double GetArea() const override final;
	double GetPerimeter() const override final;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
protected:
	void AppendProperties(std::ostream & strm) const;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
};
