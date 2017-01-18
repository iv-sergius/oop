#include "stdafx.h"
#include "SolidShape.h"
#include "Point.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint &leftTop, const CPoint &rightBottom, const std::string &outlineColor, const std::string &fillColor);

	double GetArea() const override final;
	double GetPerimeter() const override final;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
protected:
	void AppendSolidShapeProperties(std::ostream & strm) const override;
private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};
