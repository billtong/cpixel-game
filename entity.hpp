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
	bool IncludedByPoints(vector<Point> points)
	{
		// find if it is on the path
		for (int i = 0; i < points.size(); i++)
		{
			int j = (i == points.size() - 1) ? 0 : i + 1;
			int tempa = pow(m_iX - points[i].m_iX, 2.0) + pow(m_iY - points[i].m_iY, 2.0);
			int tempb = pow(m_iX - points[j].m_iX, 2.0) + pow(m_iY - points[j].m_iY, 2.0);
			int tempc = pow(points[i].m_iX - points[j].m_iX, 2.0) + pow(points[i].m_iY - points[j].m_iY, 2.0);
			if (tempa + tempb == tempc)
			{
				return true;
			}
		}
		// find if it is inside the path
		return false;
	}
};

