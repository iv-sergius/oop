// 2d.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "2d.h"

CPoint ReadPoint(std::istream & inStream)
{
	double x, y;
	if (inStream >> x && inStream >> y)
	{
		return CPoint(x, y);
	}
	else
	{
		throw std::invalid_argument("Expected 2 double values means point");
		return CPoint();
	}
}

TypeShapePtr ReadCircle(std::istream & inStream)
{
	
	CPoint center = ReadPoint(inStream);
	double radius;
	if (!(inStream >> radius)) {
		throw std::invalid_argument("Radius must be double");
	}
	std::string outlineColor, fillColor;
	inStream >> outlineColor;
	inStream >> fillColor;
	TypeShapePtr shapePtr = std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
	return shapePtr;
}

TypeShapePtr ReadRectangle(std::istream & inStream)
{
	CPoint leftTop = ReadPoint(inStream);
	CPoint rightBottom = ReadPoint(inStream);
	std::string outlineColor, fillColor;
	inStream >> outlineColor;
	inStream >> fillColor;
	return std::make_shared<CRectangle>(leftTop, rightBottom, outlineColor, fillColor);

}

TypeShapePtr ReadTriangle (std::istream & inStream)
{
	CPoint vertex1 = ReadPoint(inStream);
	CPoint vertex2 = ReadPoint(inStream);
	CPoint vertex3 = ReadPoint(inStream);
	std::string outlineColor, fillColor;
	inStream >> outlineColor;
	inStream >> fillColor;
	return std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

TypeShapePtr ReadLineSegment(std::istream & inStream)
{
	CPoint vertex1 = ReadPoint(inStream);
	CPoint vertex2 = ReadPoint(inStream);
	std::string outlineColor;
	inStream >> outlineColor;
	return std::make_shared<CLineSegment>(vertex1, vertex2, outlineColor);
}


typedef std::map<std::string, std::function<TypeShapePtr(std::istream & inStream)>> ReadShapesMap;
static const ReadShapesMap READ_MAP = {
	{ "circle", ReadCircle },
	{ "triangle", ReadTriangle },
	{ "rectangle", ReadRectangle },
	{ "line", ReadLineSegment }
};

void ReadShape(std::istream & inStream, TypeShapePtrVector & shapesVector)
{
	std::string shapeString;
	std::getline(inStream, shapeString);
	boost::to_lower(shapeString);
	std::istringstream shapeStream(shapeString);
	
	std::string shapeName;
	shapeStream >> shapeName;

	auto it = READ_MAP.find(shapeName);
	if (it != READ_MAP.end())
	{
		TypeShapePtr shapePtr;
		try
		{
			shapePtr = it->second(shapeStream);
			shapesVector.push_back(shapePtr);
//			std::cout << shapePtr
		}
		catch (const std::invalid_argument &ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Unknown shape name" << std::endl;
	}
}

void PrintMaxAreaShape(const TypeShapePtrVector &shapesVector)
{
	if (!shapesVector.empty())
	{
		auto minShapePtr = std::max_element(shapesVector.begin(), shapesVector.end(), [](const auto &lhs, const auto &rhs){
			return lhs->GetArea() > rhs->GetArea();
		});
		std::cout << "Maximun area shape is " << (*minShapePtr)->ToString() << std::endl;
	}
}

void PrintMinPerimeterShape(const TypeShapePtrVector &shapesVector)
{
	if (!shapesVector.empty())
	{
		auto minShapePtr = std::min_element(shapesVector.begin(), shapesVector.end(), [](const auto &lhs, const auto &rhs) {
			return lhs->GetPerimeter() > rhs->GetPerimeter();
		});
		std::cout << "Minimum perimeter shape is " << (*minShapePtr)->ToString() << std::endl;
	}
}

void PrintShape(const TypeShapePtrVector &shapesVector)
{
	for (auto it = shapesVector.begin(); it != shapesVector.end(); ++it)
		std::cout << (*it).get()->ToString();
}
