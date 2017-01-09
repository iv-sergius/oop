#include "stdafx.h"
#include "SolidShape.h"
#include "Point.h"

class CRectangle : public ISolidShape
{
public:
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	CPoint GetWidth() const;
	CPoint GetHeight() const;
private:
	CPoint m_leftTopVertex;
	CPoint m_size;
};
