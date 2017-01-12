#include "stdafx.h"
#include "SolidShape.h"
#include "Point.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint &leftTop, const CPoint &rightBottom, const std::string &outlineColor, const std::string &fillColor);

	double GetArea() const;
	double GetPerimeter() const;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
protected:
	void CRectangle::AppendProperties(std::ostream & strm) const;
private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};
