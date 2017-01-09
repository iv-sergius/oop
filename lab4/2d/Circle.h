#include "stdafx.h"
#include "SolidShape.h"
#include "Point.h"

class CCircle : public ISolidShape
{
public:
	CPoint GetCenter();
	CPoint GetRadius();
private:
	CPoint m_center;
	double m_radius;
};