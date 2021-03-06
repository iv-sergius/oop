#include "stdafx.h"
#include "SolidShape.h"
#include "Point.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(const CPoint &vertex1, const CPoint &vertex2, const CPoint &vertex3, const std::string &outlineColor, const std::string &fillColor);

	double GetArea() const override final;
	double GetPerimeter() const override final;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
protected:
	void AppendSolidShapeProperties(std::ostream & strm) const override;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};
