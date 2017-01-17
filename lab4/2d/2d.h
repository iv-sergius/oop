#pragma once

#include "stdafx.h"
#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "SolidShape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"


typedef std::shared_ptr<IShape> TypeShapePtr;
// typedef IShape * TypeShapePtr;
typedef std::vector<TypeShapePtr> TypeShapePtrVector;

void ReadShape(std::istream &inStream, TypeShapePtrVector &vector);

void PrintShape(const TypeShapePtrVector &shapesVector);
void PrintMaxAreaShape(const TypeShapePtrVector &shapeVector);
void PrintMinPerimeterShape(const TypeShapePtrVector &shapeVector);









