#pragma once

#include "stdafx.h"
#include "../Point.h"
#include "../Shape.h"
#include "../Line.h"
#include "../SolidShape.h"
#include "../Circle.h"
#include "../Rectangle.h"
#include "../Triangle.h"

static const double R_EPS = 1e-10;

void VerifyDouble(const double value, const double expectedValue);

void VerifyPoint(const CPoint &point, double x, double y);

void VerifyPoint(const CPoint &point, const CPoint &expectedPoint);

void VerifyLineSegment(const CLineSegment &line, const CPoint &expectedStart, const CPoint &expectedEnd, const std::string &expectedColor);

void VerifyCircle(const CCircle &circle, const CPoint &expectedCenter, double expectedRadius, const std::string &expectedOutlineColor, const std::string &expectedFillColor);

void VerifyRectangle(const CRectangle &rectangle, const CPoint &expectedLeftTop, const CPoint &expectedRightBottom, const std::string &expectedOutlineColor, const std::string &expectedFillColor);

void VerifyTriangle(const CTriangle &triangle, const CPoint &expectedVertex1, const CPoint &expectedVertex2, const CPoint &expectedVertex3, const std::string &expectedOutlineColor, const std::string &expectedFillColor);
