#include "stdafx.h"
#include "Shape.h"



std::string IShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void IShape::SetOutlineColor(const std::string & stringColor)
{
	if (stringColor.length() != 6)
	{
		throw std::invalid_argument("Color must be string with length = 6");
	}
	std::string colorToSave;
	for (size_t i = 0; i < stringColor.length(); ++i)
	{
		char ch = stringColor[i];
		if (isdigit(ch) || (ch >= 'a' && ch <= 'f'))
		{
			colorToSave.push_back(ch);
		}
		else if (ch >= 'A' && ch <= 'F')
		{
			colorToSave.push_back(ch - 'A' + 'a');
		}
		else
		{
			throw std::invalid_argument("Color string must contain only hex symbols");
		}
	}
	m_outlineColor = colorToSave;
}
