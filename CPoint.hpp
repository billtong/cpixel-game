#pragma once

#include <core/SkCanvas.h>
#include <vector>
#include <cmath>

#include "variables.h"

using std::vector;

class CPoint
{
public:
	SkScalar m_iX;
	SkScalar m_iY;

	CPoint(SkScalar x, SkScalar y) : m_iX(x), m_iY(y) {}

	bool operator==(const CPoint& point)
	{
		return m_iX == point.m_iX && m_iY == point.m_iY;
	}

	static bool TwoPointsIntersectPoints(CPoint p1, CPoint p2, vector<CPoint> points)
	{
		for (int i = 0; i < points.size(); i++)
		{
			int j = (i == points.size() - 1) ? 0 : i + 1;
			if (p1.m_iX == points[i].m_iX && p1.m_iX == points[j].m_iX && p2.m_iX == points[i].m_iX && p2.m_iX == points[j].m_iX)
			{
				if (points[i].m_iY > points[j].m_iY)
					return (points[i].m_iY >= p1.m_iY && points[j].m_iY <= p1.m_iY) || (points[i].m_iY >= p2.m_iY && points[j].m_iY <= p2.m_iY);
				else
					return (points[j].m_iY >= p1.m_iY && points[i].m_iY <= p1.m_iY) || (points[j].m_iY >= p2.m_iY && points[i].m_iY <= p2.m_iY);
			}
			if (p1.m_iY == points[i].m_iY && p1.m_iY == points[j].m_iY && p2.m_iY == points[i].m_iY && p2.m_iY == points[j].m_iY)
			{
				if (points[i].m_iX > points[j].m_iX)
					return (points[i].m_iX >= p1.m_iX && points[j].m_iX <= p1.m_iX) || (points[i].m_iX >= p2.m_iX && points[j].m_iX <= p2.m_iX);
				else
					return (points[j].m_iX >= p1.m_iX && points[i].m_iX <= p1.m_iX) || (points[j].m_iX >= p2.m_iX && points[i].m_iX <= p2.m_iX);
			}

		}
		return false;
	}

	bool IncludedByPointPaths(vector<CPoint> points)
	{
		for (int i = 0; i < points.size(); i++)
		{
			int j = (i == points.size() - 1) ? 0 : i + 1;
			if (m_iX == points[i].m_iX && m_iX == points[j].m_iX)
			{
				if (points[i].m_iY > points[j].m_iY)
				{
					return points[i].m_iY >= m_iY && points[j].m_iY <= m_iY;
				}
				else {
					return points[j].m_iY >= m_iY && points[i].m_iY <= m_iY;
				}
			}
			if (m_iY == points[i].m_iY && m_iY == points[j].m_iY)
			{
				if (points[i].m_iX > points[j].m_iX)
				{
					return points[i].m_iX >= m_iX && points[j].m_iX <= m_iX;
				}
				else {
					return points[j].m_iX >= m_iX && points[i].m_iX <= m_iX;
				}
			}
		}
		return false;
	}
};

