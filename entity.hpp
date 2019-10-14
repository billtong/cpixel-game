#pragma once

#include <core/SkCanvas.h>
#include <vector>
#include <cmath>

using std::vector;

typedef struct _offset
{
	SkScalar w;
	SkScalar h;
	SkScalar x;
	SkScalar y;
} Offset;

class Point
{
public:
	SkScalar m_iX;
	SkScalar m_iY;
public:
	Point(SkScalar x, SkScalar y) : m_iX(x), m_iY(y) {}
	
	bool operator==(const Point& point)
	{
		return m_iX == point.m_iX && m_iY == point.m_iY;
	}

	bool IncludedByPoints(vector<Point> points)
	{
		// find if it is on the path
		for (int i = 0; i < points.size(); i++)
		{
			int j = (i == points.size() - 1) ? 0 : i + 1;
			if (m_iX == points[i].m_iX && m_iX == points[j].m_iX)
			{
				SkScalar a = abs(m_iY - points[i].m_iY);
				SkScalar b = abs(m_iY - points[j].m_iY);
				SkScalar c = abs(points[i].m_iY - points[j].m_iY);
				return (a + b) == c;
			}
			if (m_iY == points[i].m_iY && m_iY == points[j].m_iY)
			{
				SkScalar a = abs(m_iX - points[i].m_iX);
				SkScalar b = abs(m_iX - points[j].m_iX);
				SkScalar c = abs(points[i].m_iX - points[j].m_iX);
				return (a + b) == c;
			} 
			/*
				double tempa = pow(m_iX - points[i].m_iX, 2.0) + pow(m_iY - points[i].m_iY, 2.0);
				double tempb = pow(m_iX - points[j].m_iX, 2.0) + pow(m_iY - points[j].m_iY, 2.0);
				double tempc = pow(points[i].m_iX - points[j].m_iX, 2.0) + pow(points[i].m_iY - points[j].m_iY, 2.0);
				if (abs(tempa + tempb - tempc) <=1 )
				{
					return true;
				}
			*/
		}
		// find if it is inside the path
		return false;
	}
};

