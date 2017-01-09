#include "stdafx.h"
#include "SolidShape.h"
#include "Point.h"

class CTraingle : public ISolidShape
{
public:
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};