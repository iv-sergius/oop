#include "stdafx.h"
#include "Shape.h"

std::string CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string NormalizeColor(const std::string & stringColor)
{
	if (stringColor.length() != 6)
	{
		throw std::invalid_argument("Color must be string with length = 6");
	}
	std::string normalColor;
	for (size_t i = 0; i < stringColor.length(); ++i)
	{
		char ch = stringColor[i];
		if (isdigit(ch) || (ch >= 'a' && ch <= 'f'))
		{
			normalColor.push_back(ch);
		}
		else if (ch >= 'A' && ch <= 'F')
		{
			normalColor.push_back(ch - 'A' + 'a');
		}
		else
		{
			throw std::invalid_argument("Color string must contain only hex symbols");
		}
	}
	return normalColor;
}

CShape::CShape(const std::string & typeName, const std::string & outlineColor)
	: m_typeName(typeName)
	, m_outlineColor(NormalizeColor(outlineColor))
{

}

std::string CShape::ToString() const
{
	std::ostringstream strm;
	strm << m_typeName << ":" << std::endl << std::fixed << std::setprecision(3);
	AppendProperties(strm);
	strm << "\toutline color = #" << GetOutlineColor() << std::endl
		<< "\tarea = " << GetArea() << std::endl
		<< "\tperimeter = " << GetPerimeter() << std::endl;
	return strm.str();
}
