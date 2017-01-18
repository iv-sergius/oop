#include "stdafx.h"
#include "SolidShape.h"

CSolidShape::CSolidShape(const std::string & typeName, const std::string & outlineColor, const std::string & fillColor)
	: CShape(typeName, outlineColor)
	, m_fillColor(NormalizeColor(fillColor))
{
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

std::string CSolidShape::ToString() const
{
	return CShape::ToString();
}

void CSolidShape::AppendProperties(std::ostream & strm) const
{
	AppendSolidShapeProperties(strm);
	strm << "\tfill color = #" << GetFillColor() << std::endl;
}

void CSolidShape::AppendSolidShapeProperties(std::ostream & strm) const
{
}
