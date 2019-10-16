#pragma once

#include<string>
#include<vector>
#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkString.h>

#include "CPoint.hpp"
#include "variables.h"

using std::string;
using std::vector;

class CWall
{
public:
	vector<Point> m_gPoints;
	const int* m_gRGB;
public:
	CWall(vector<Point> points, const int* rgb) {
		m_gPoints = points;
		m_gRGB = rgb;
	}
	void Draw(SkCanvas& canvas, SkPaint& paint)
	{
		SkPath path;
		path.moveTo(m_gPoints[0].m_iX, m_gPoints[0].m_iY);
		for (int i = 1; i < m_gPoints.size(); i++)
			path.lineTo(m_gPoints[i].m_iX, m_gPoints[i].m_iY);
		path.close();
		paint.setStyle(SkPaint::kStrokeAndFill_Style);
		paint.setARGB(0xFF, m_gRGB[0], m_gRGB[1], m_gRGB[2]);
		canvas.drawPath(path, paint);
	}
};