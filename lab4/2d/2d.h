#pragma once

#include "stdafx.h"

class CPoint
{
public:
	double x = 0;
	double y = 0;
};

class IShape
{
public:
	virtual double GetArea() const;
	virtual double GetPerimeter() const;
	virtual std::string ToString() const;
	virtual std::string GetOutlineColor() const;
};

class ISolidShape : public IShape
{
public:
	std::string GetFillColor() const;
private:
	std::string m_color;
};

class CLineSegment : public IShape
{
public:
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
private:
};

class CTraingle : public ISolidShape
{
public:
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
};

class CRectangle : public ISolidShape
{
public:
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	CPoint GetWidth() const;
	CPoint GetHeight() const;
};

class CCircle : public ISolidShape
{
public:
	CPoint GetCenter();
	CPoint GetRadius();
};